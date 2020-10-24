#ifndef PREDICTIVEPARSER_STACK_H
#define PREDICTIVEPARSER_STACK_H

struct s_stack;

typedef struct s_stack* stack;

stack create_stack();

void push(stack s, char element);

char pop(stack s);

char stack_top(stack s);

void dealloc_stack(stack s);

#endif
