#ifndef KV_H
#define KV_H

#define MAX_KEY_LENGTH 16
#define MAX_VALUE_LENGTH 128


/*
 * Structure to for a list of key-value pairs
 */

typedef struct keyValue {
    char key [ MAX_KEY_LENGTH ];
    char value [ MAX_VALUE_LENGTH ];
    struct keyValue *pNext;
} kv;


/*
 * Create an empty key-value list
 */

kv *newKvList ( void );


/*
 * Append a new key-value pair to a linked list
 */

void appendKv (
    kv **ppRoot, 
    char *key, 
    char *value
);


/*
 * Get the value back that corresponds to a key,
 * or NULL if the key is not found
 */

char *getValue (
    kv *ppRoot, 
    char *key
);


/*
 * Parse a buffer for key-value pairs
 * 
 * Return a linked list of key-values found
 * or NULL if nothing found.
 * 
 * The format of data in the buffer should be:
 * key1 value1
 * key2 value2
 * 
 * key - only contains alphanumeric characters
 * whitespace terminates the key
 * value - all characters until the end of the line/buffer
 */

kv *parseKv (
    char *buffer
);

/*
 * Serialise a linked list of key-value pairs into a string
 * 
 * kv - linked list of key-value pairs
 * pBuffer - contains serialised result
 * 
 * Results of this serialisation should parse with parseKv
 * without error
 */

int serialiseKv(
    kv *pKv,
    char *pBuffer,
    size_t bufferLen
);

/*
 * Free all key-value pairs in a linked list
 */

void freeKv (
    kv *pKv
);


#endif
