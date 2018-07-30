#ifndef KEYVALUE_H
#define KEYVALUE_H

typedef struct kv {
    char *key;
    char *value;
    struct kv *next;
} key_value_pair;


key_value_pair *new_kv(char *key, char *value); /* initialises kv pair */
void free_kv(key_value_pair *kv);
key_value_pair *parse_kv(char *buffer);
char *get_value(key_value_pair *kv, char* key);

#endif