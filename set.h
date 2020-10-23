#ifndef PREDICTIVEPARSER_SET_H
#define PREDICTIVEPARSER_SET_H

#include <stdlib.h>
#include <stdbool.h>

struct set_s{
    ssize_t length; // Length of set
    char *elements; // Array of elements in set
    int index; // last index
};

typedef struct set_s *set;

set create_set(ssize_t);
void set_add(set, char);
set get_set_from_array(char*, ssize_t);
void set_union(set, set);
void set_remove(set, char);
int set_contains(set, char);
bool is_set_singleton(set s);
void print_set(set);
int get_set_size(set s);
void set_dealloc(set s);
#endif
