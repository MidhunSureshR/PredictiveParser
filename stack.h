#ifndef PREDICTIVEPARSER_STACK_H
#define PREDICTIVEPARSER_STACK_H

typedef struct{
    char elements[100];
    int top;
}_stack;

typedef _stack* stack;

stack create_stack();

void push(stack s, const char element);

char pop(stack s);

char stack_top(stack s);

void dealloc_stack(stack s);

#endif
