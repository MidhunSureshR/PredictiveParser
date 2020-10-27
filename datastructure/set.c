#include "set.h"
#include <stdio.h>

// Find union of two sets and store in destination
void set_union(set destination, set source){
    for(ssize_t i=0; i<source->index; ++i){
        set_add(destination, source->elements[i]);
    }
}

// Create a set with length number of elements
set create_set(ssize_t length){
    set s = malloc(sizeof(struct set_s));
    s->elements = malloc(sizeof(char) * length);
    s->length = length;
    s->index = 0;
    return s;
}

// Add element to set
void set_add(set s, char element){
    if(set_contains(s, element) != -1) return;
    s->elements[s->index++] = element;
}

// Get a set from array
set get_set_from_array(char *array, ssize_t len){
    set s = malloc(sizeof(set));
    s->length = len;
    s->elements = malloc(sizeof(char) * len);
    for(int i=0; i<s->length; ++i) s->elements[i] = array[i];
    return s;
}

int set_contains(set s, char element){
    for(ssize_t i=0; i<s->index; ++i){
        if(s->elements[i] == element) return i;
    }
    return -1;
}

bool is_set_singleton(set s){
    return s->index == 1 ? true: false;
}

void set_remove(set s, char element){
    int pos = set_contains(s, element);
    if(pos == -1) return;
    for(ssize_t i=pos; i<s->index-1; ++i){
        s->elements[i] = s->elements[i+1];
    }
    s->length = s->length -1;
    s->index = s->index -1;
}

void print_set(set s){
    printf("{");
    for(ssize_t i=0; i<s->index-1; ++i) {
        printf("%c, ",s->elements[i]);
    }
    printf("%c}\n", s->elements[s->index - 1]);
}

int get_set_size(set s){
    return s->index;
}

void set_dealloc(set s){
    free(s->elements);
    free(s);
}