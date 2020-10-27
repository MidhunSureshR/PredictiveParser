#ifndef PREDICTIVEPARSER_PRODUCTION_H
#define PREDICTIVEPARSER_PRODUCTION_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    char* production;
}production_body;

typedef struct{
    ssize_t size;
    production_body* body;
}production_body_list;

typedef struct{
    char left;
    production_body_list *right;
}production;

void print_production(production*);
void get_production_as_string(char*, production*);
production* parse_production_from_string(const char*);
production* get_production_of_nonterminal(char non_terminal, production **grammar, ssize_t num_productions);
bool is_terminal(char c);
bool is_nonterminal(char c);
production** get_production_from_string_collection(char **grammar, int num_productions);

#endif
