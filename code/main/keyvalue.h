#ifndef KEYVALUE_H
#define KEYVALUE_H

typedef struct kv {
    char *key;
    char *value;
    struct kv *next;
} key_value_pair;


#endif