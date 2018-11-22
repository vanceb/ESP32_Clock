#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_log.h"
#include "kv.h"

#define TAG "KV"

int is_space(char c)
{
    return ( c == ' ' ) || ( c == '\t' ) || ( c == '\r' ) || ( c == '\n' ) || ( c == '\f' ) ;
}

int is_alpha ( char c )
{
    return (( 'a' <= c) && ( c <= 'z' )) || ( ( 'A' <= c ) && ( c <= 'Z' ) );
}

int is_digit ( char c )
{
    return ( '0' <= c ) && (c <= '9' ); 
}

int is_alnum ( char c )
{
    return is_digit(c) || is_alpha(c);
}

void appendKv (
    kv **ppRoot, 
    char *key, 
    char *value
)
{
    /* Create a new key-value pair structure */
    kv *newKv = ( kv * ) malloc ( sizeof ( kv ) );
    strcpy( newKv->key, key );
    strcpy( newKv->value, value );
    newKv->pNext = NULL;

    /* Walk the list to the last node */
    while ( *ppRoot ) {
        ppRoot = &( ( *ppRoot ) -> pNext );
    }

    /* Append new structure to the list */
    *ppRoot = newKv;
}


char *getValue (
    kv *pRoot, 
    char *key
)
{
    /* Walk the list */
    while ( pRoot ) {

        /* Does this node match the key? */
        if ( ! strcmp( pRoot->key, key ) ) {
        
            /* Return the value */
            return pRoot->value;
        }
        pRoot = pRoot -> pNext;
    }
    /* Not matched */
    return NULL;
}


int parseSingleKv ( 
    kv **ppKv,
    char **pBuffer ) 
{

    /* Make sure our buffer has something in it */
    if ( ! **pBuffer ) {
        return 0;
    }

    /* Make a note of the start position */
    char *bufferStart = *pBuffer;

    /* Eat whitespace */
    while ( is_space( **pBuffer ) ) {

        (*pBuffer)++;
    }

    /* Get key */
    
    /* Set the start of the key in the buffer */
    char *kStart = *pBuffer;
    
    /* Key can contain alphanumeric chars plus '-' '_' */
    while ( is_alnum ( **pBuffer ) || 
            **pBuffer == '_' ||
            **pBuffer == '-' ) 
    {

        (*pBuffer)++;
    }

    /* Check the key has some characters */
    if ( (*pBuffer - kStart) == 0 ) {
        
        /* Invalid format */
        return -1;
    }

    /* Check that we have a valid separator */
    if ( ( ! ( **pBuffer == ' ') ) &&
         ( ! ( **pBuffer == '\t' ) ) )
    {

        /* Invalid format */
        return -1;
    }

    /* Mark the end of the key */
    **pBuffer = '\0';
    (*pBuffer)++;

    /* Get value */

    /* Eat spaces and tabs */
    while ( **pBuffer == ' ' ||
            **pBuffer =='\t' ) 
    {

        (*pBuffer)++;
    }

    /* We should be at the start of the value */
    char *vStart = *pBuffer;

    /* Confirm we haven't hit the end of the buffer */
    if ( ! **pBuffer ) 
    {

        /* Invalid format */
        return -1;
    }

    /* Get ready to mark the last non whitespace 
     * character with a cursor */
    char *cursor = NULL;

    /* Scan until end of line or buffer */
    while ( **pBuffer != '\n' &&
            **pBuffer != '\0' )
    {
        if ( ! is_space ( **pBuffer ) )
            cursor = *pBuffer;
        (*pBuffer)++;
    }

    if ( ( cursor != NULL ) && ( ++cursor != *pBuffer ) )
    {
        /* We have removed some whitespace */
        *cursor = '\0';
    } else {
        ESP_LOGD(TAG, "No Trailing Space!!!!!");
    }

    /* If end of line then mark the end of the value
     * and move to next character ready for next call */
    if ( **pBuffer == '\n' ) 
    {
        **pBuffer = '\0';
        (*pBuffer)++;
    }

    /* Confirm the value has some characters */
    if ( (cursor - vStart) <= 0) 
    {
        /* Invalid Format */
        return -1;
    }

    /* Append the key-value pair to the list */
    appendKv(ppKv, kStart, vStart);

    /* Return the number of characters read from the buffer */
    return *pBuffer - bufferStart;
}


kv *parseKv (
    char *buffer
)
{
    /* Create a new kv linked list */
    kv *pRoot = NULL;

    /* Walk over the buffer */
    while ( *buffer ) {

        parseSingleKv(&pRoot, &buffer);
    }

    return pRoot;
}


void freeKv (
    kv *pKv
)
{

    /* Free your children */
    if ( pKv -> pNext ) {
        freeKv ( pKv -> pNext );
    }

    /* Free yourself */
    free ( pKv );
}

/*
int main () {
    char parseThis[] = "k1 vl     \nk2 v2\n k3 v3\n k4 v4";
    kv *kvList = parseKv(parseThis);
     while (kvList != NULL) {
        printf("'%s'", kvList -> key);
        printf("\t");
        printf("'%s'", kvList -> value);
        printf("\n");
        kvList = kvList -> pNext;
    }
}
*/