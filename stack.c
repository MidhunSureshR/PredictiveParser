#include "stack.h"
#include <stdlib.h>

stack create_stack() {
    stack s = malloc(sizeof(_stack));
    s->top = -1;
    return s;
}

void push(stack s, const char element) {
    if(element == '.') return; // Do Not Push Epsilon
    s->top++;
    s->elements[s->top] = element;
}

char pop(stack s) {
    const char element = s->elements[s->top];
    s->top--;
    return element;
}

char stack_top(stack s) {
    return s->elements[s->top];
}

void dealloc_stack(stack s) {
    free(s);
}
