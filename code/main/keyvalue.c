#include "keyvalue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

key_value_pair *new_kv(char *key, char *value) /* initialises kv pair */
{
    key_value_pair *kv = (key_value_pair *) malloc(sizeof(key_value_pair));
    if (key != NULL)
        kv->key = strdup(key);
    else
        kv->key = NULL;
    if (value != NULL)
        kv->value = strdup(value);
    else
        kv->value = NULL;
    kv->next = NULL;
    return kv;
}

void free_kv(key_value_pair *kv)
{
    if (kv->next) {
        free_kv(kv->next);
    }
    free(kv->key);
    free(kv->value);
    free(kv);
}


key_value_pair *parse_kv(char *buffer)
{
    int i;
    char *start_k, *start_v;
    /* Eat whitespace */
    for (i=0; buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n'; ++i)
        ;
    /* Note start of the key */    
    start_k = &buffer[i];
    for (; buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n'; ++i)
        ;
    if (buffer[i] == '\n') {
        /* This should not happen in a well formatted buffer */
        return NULL;
    }
    buffer[i++] = '\0'; /* Allow key string to be read directly from the buffer */
    /* Eat whitespace */
    for (; buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n'; ++i)
        ;
    /* Note start of the value */    
    start_v = &buffer[i];
    /* Should be terminated with a newline */
    for (; buffer[i] != '\n'; ++i)
        ;
    buffer[i++] = '\0'; /* Allow key string to be read directly from the buffer */
    return new_kv(start_k, start_v);
}


int parse_one_kv(char *buffer, key_value_pair *kv)
{
    char *start, *start_k, *start_v;
    key_value_pair *root;

    root = kv;
    start = buffer;

    /* Eat whitespace */
    for (; *buffer == ' ' || *buffer == '\t' || *buffer == '\n' || *buffer == EOF; ++buffer)
        ;
    if (*buffer == EOF)
    {
        return -1;
    } else {
        /* Note start of the key */    
        start_k = buffer;
    }
    /* Move forward to the first whitespace character, should be ' ' or '\t' */
    for (; *buffer != ' ' && *buffer != '\t' && *buffer != '\n' && *buffer != EOF; ++buffer)
        ;
    /* Check for EOF */
    if (*buffer == EOF)
        return -1;

    if (*buffer == '\n') {
        /* This should not happen in a well formatted buffer */
        return -2;
    }
    *buffer++ = '\0'; /* Allow key string to be read directly from the buffer */
    /* Eat whitespace */
    for (; *buffer == ' ' || *buffer == '\t' || *buffer == '\n' || *buffer == EOF; ++buffer)
        ;
    /* Check for EOF */
    if (*buffer == EOF)
        return -1;
    /* Note start of the value */    
    start_v = buffer;
    /* Should be terminated with a newline */
    for (; *buffer != '\n' && *buffer != EOF; ++buffer)
        ;
    /* Check for EOF */
    if (*buffer == EOF)
        return -1;
    *buffer++ = '\0'; /* Allow key string to be read directly from the buffer */

    /* Work to the end of the list of KV */
    while (kv->next != NULL)
        kv = kv->next;
    kv->next = new_kv(start_k, start_v);
    return buffer - start;
}


int main()
{
    int i;
    char inbuff[256];
    char * cursor;
    key_value_pair *kv;

    printf("Please input key value to be parsed: \n");
    for (i=0; (inbuff[i] = getchar()) != EOF; i++)
        ;
    inbuff[i] = '\0';

/*
    kv = parse_kv(inbuff);
    printf("Key: %s\n", kv->key);
    printf("Value: %s\n", kv->value);
*/
    i = 0;
    cursor = inbuff;
    kv = new_kv(NULL,NULL);
    while ((i = parse_one_kv((cursor += i), kv)) > 0)
        ;

    while ((kv = kv->next) != NULL) { 
        if (kv->key != NULL && kv->value != NULL) {
            printf("Key: %s\n", kv->key);
            printf("Value: %s\n\n", kv->value);
        }
    } 
    
}