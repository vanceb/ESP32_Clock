#ifndef KEYVALUE_H
#define KEYVALUE_H

/* 
 * If STATIC_KEY_VALUE is defined then memory for the key and value
 * are statically allocated to the sizes defined below.  Otherwise
 * they are dynamically allocated according to the length of the
 * MAX_ values below.
 */
#define STATIC_KEY_VALUE 0
#define MAX_KEY_LEN 16
#define MAX_VALUE_LEN 128


typedef struct kv {
    #ifndef STATIC_KEY_VALUE
    char *key;
    char *value;
    #else
    char key[MAX_KEY_LEN];
    char value[MAX_VALUE_LEN];
    #endif
    struct kv *next;
} key_value_pair;


key_value_pair *new_kv(char *key, char *value); /* initialises kv pair */
void free_kv(key_value_pair *kv);
key_value_pair *parse_kv(char *buffer);
char *get_value(key_value_pair *kv, char* key);

#endif