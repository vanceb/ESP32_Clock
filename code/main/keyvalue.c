#include "keyvalue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


/* 
 * Create a new key_value_pair strcuture with memory allocation
 * If key and value are provided (i.e. not NULL) they will be
 * copied and linked into the structure
 * 
 * Parameters:
 * 
 * key - a c string holding the key
 * value = a c string holding the value
 * 
 * Returns:  The newly allocated and initialised key_value_pair
 */
key_value_pair *new_kv(char *key, char *value) /* initialises kv pair */
{
    key_value_pair *kv = (key_value_pair *) malloc(sizeof(key_value_pair));

    #ifndef STATIC_KEY_VALUE

    if (key != NULL)
        kv->key = strdup(key);
    else
        kv->key = NULL;
    if (value != NULL)
        kv->value = strdup(value);
    else
        kv->value = NULL;

    #else

    if (key != NULL) {
        strncpy(kv->key, key, MAX_KEY_LEN - 1);
        kv->key[MAX_KEY_LEN] = '\0';
    } else {
        kv->key[0] = '\0';
    }
    if (value != NULL) {
        strncpy(kv->value, value, MAX_VALUE_LEN);
        kv->value[MAX_VALUE_LEN - 1] = '\0';
    } else {
        kv->value[0] = '\0';
    }

    #endif

    kv->next = NULL;
    return kv;
}


/*
 * Frees all memory allocated to a linked list of key_value_pairs
 * from the key_value_pair pointed to by kv.
 * i.e.  It frees all down-list key_value_pairs
 */
void free_kv(key_value_pair *kv)
{
    if (kv != NULL) {
        /* Walk to the bottom of the linked list recursively */
        if (kv->next) {
            free_kv(kv->next);
        }

        #ifndef STATIC_KEY_VALUE
        /* If we are dynamically allocating memory for the key and value then free that */
        free(kv->key);
        free(kv->value);

        #endif

        /* Free the main structure */
        free(kv);
    }
}


/*
 * Parse a single key-value pair from a buffer and add it to the end of a linked list
 * A key value pair should have the following format:
 * 
 * The key and the value should occupy a single line
 * 
 * key 
 *      - Starts at the first non-whitespace character
 *      - Continues until the next whitespace character (should not be '\n')
 * 
 * value
 *      - Starts at the first non-whiotespace character after the end of the key
 *      - Continues up to but not including the '\n'
 * 
 * Parameters:
 * 
 * buffer - The string buffer to parse for key-value pair.  This buffer is modified
 *          in place with the addition of '\0' to mark the end of the key and value.
 * 
 * kv - The root of a key_value_pair linked list, to which the parsed key value pair
 *      will be appended
 * 
 * Returns - The number of characters consumed in finding the key-value pair
 *          -1 if EOF is found
 *          -2 if there is a format error when parsing
 */
int parse_one_kv(char *buffer, key_value_pair *kv)
{
    char *start, *start_k, *start_v;
    key_value_pair *root;

    root = kv;
    start = buffer;

/* Look for the key */
    /* Eat whitespace */
    for (; isspace((int) *buffer); ++buffer)
        ;
    /* Check for end of the input */
    if (*buffer == '\0')
        return -1;
    /* Note start of the key */    
    start_k = buffer;
    /* Move forward to the first non-alphanumeric character */
    for (; isalnum((int) *buffer); ++buffer)
        ;
    /* Check for end of the input */
    if (*buffer == '\0' || *buffer == '\n') {
        /* This should not happen in a well formatted buffer */
        return -2;
    }
    *buffer++ = '\0'; /* Allow key string to be read directly from the buffer */

/* Look for value */
    /* Eat whitespace */
    for (; isspace((int) *buffer); ++buffer)
        ;
    /* Check for end of the input */
    if (*buffer == '\0' || *buffer == '\n') {
        /* This should not happen in a well formatted buffer */
        return -2;
    }
    /* Note start of the value */    
    start_v = buffer;
    /* Should be terminated with a newline */
    for (; *buffer != '\n'; ++buffer)
        ;
    *buffer++ = '\0'; /* Allow key string to be read directly from the buffer */

    /* Work to the end of the list of KV */
    while (kv->next != NULL)
        kv = kv->next;
    kv->next = new_kv(start_k, start_v);
    return buffer - start;
}


/*
 * Parses all key_value_pairs found in the buffer, until...
 *  - It reaches EOF or the end of the string ('\0')
 *  - The parsing comes across an error in formatting
 * 
 * Parameters:
 * buffer - The buffer to be parsed for key_value_pairs
 * 
 * Returns:  The root node of a linked list of parsed key_value_pairs
 */
key_value_pair *parse_kv(char *buffer)
{
    key_value_pair *kv;
    int i;
    kv = new_kv(NULL,NULL);
    for (; (i=parse_one_kv(buffer, kv)) > 0; buffer+=i)
        ;
    return kv;
}

/*
 * Search the linked list of key_value_pairs for a key
 * 
 * Parameters:
 * kv - The root of the linked list of key_value_pairs
 * key - The key to search for
 * 
 * Returns:  The value associated with the first occurance of key
 *          or an empty c string if the key is not found
 */
char *get_value(key_value_pair *kv, char* key) 
{
    /* The root node has no content, so safe to go to second */
    while ((kv = kv->next) != NULL) {
        if (strcmp(kv->key, key) == 0) {
            return kv->value;
        }
    } 
    return "\0";
}


/*
 * A main function to allow interactive testing of functionality
 */
/*
int main()
{
    int i;
    int inbuff[256];
    key_value_pair *kv, *root;

    printf("Please input key value to be parsed: \n");
    for (i=0; (inbuff[i] = getchar()) != EOF; i++)
        ;
    inbuff[i] = '\0';

    root = parse_kv(inbuff);
    kv = root;

    while ((kv = kv->next) != NULL) { 
        if (kv->key != NULL && kv->value != NULL) {
            printf("Key: %s\n", kv->key);
            printf("Value: %s\n\n", kv->value);
        }
    } 

    printf("Value of SVB: %s\n", get_value(root, "SVB"));
    
}
*/