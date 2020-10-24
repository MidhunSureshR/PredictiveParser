#include "p_parser.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
    char elements[100];
    int top;
}_stack;

typedef _stack* stack;

stack create_stack(){
    stack s = malloc(sizeof(_stack));
    s->top = -1;
    return s;
}

void push(stack s, const char element){
    if(element == '.') return; // Do Not Push Epsilon
    s->top++;
    s->elements[s->top] = element;
}

char pop(stack s){
    const char element = s->elements[s->top];
    s->top--;
    return element;
}

char stack_top(stack s){
    return s->elements[s->top];
}

void dealloc_stack(stack s){
    free(s);
}

void error(stack s){
    printf("Error in parsing\n");
    dealloc_stack(s);
}

void predictive_parse(const char* string, table parsing_table, production** grammar){
    const int buffer_length = strlen(string) + 1;
    char *input_buffer = malloc(sizeof(char) * buffer_length);
    strncpy(input_buffer, string, strlen(string));
    char *current_symbol = input_buffer;
    // Add end marker ($) to end of input buffer
    input_buffer[buffer_length-1] = '$';

    // Create initial config of array
    stack s = create_stack();
    push(s,'$');
    const char starting_symbol = grammar[0]->left;
    push(s, starting_symbol);
    printf("Attempting follow productions:\n");
    while(stack_top(s) != '$'){

        const char s_top = stack_top(s);
        if(s_top == *current_symbol){
            pop(s);
            current_symbol++;
        }
        else if(is_terminal(s_top)){
            error(s);
            return;
        }
        else if(table_get_entry(parsing_table, s_top, *current_symbol) == NULL){
            error(s);
            return;
        }
        else{
            table_entry* t = table_get_entry(parsing_table, s_top, *current_symbol);
            production_body sub_production = t->p->right->body[t->sub_production_index];
            const int strlen_sub_production = strlen(sub_production.production);
            pop(s);
            printf("\t%c->%s\n",t->p->left, sub_production.production);
            for(int i=strlen_sub_production-1; i>=0; --i){
                push(s, sub_production.production[i]);
            }
        }
    }
    printf("Parsing is successful!!\n");
}