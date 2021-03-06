#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "production.h"
#include "../helpers/string_helper.h"
#include <ctype.h>

void print_production(production *p){
    printf("%c->", p->left);
    int i;
    for(i=0; i<p->right->size - 1; ++i){
        printf("%s|",p->right->body[i].production);
    }
    printf("%s\n",p->right->body[i].production);
}

void get_production_as_string(char *string, production *p){
    sprintf(string, "%c->", p->left);
    int i;
    for(i=0; i<p->right->size - 1; ++i){
        sprintf(strchr(string, '\0'),"%s|",p->right->body[i].production);
    }
    sprintf(strchr(string, '\0'),"%s",p->right->body[i].production);
}

production_body_list* parse_production_body_from_string(const char* start_of_production_body){
    char backup[100];
    copy_string(backup, start_of_production_body);

    production_body_list* p = malloc((sizeof(production_body_list)));
    p->size = num_occurrence(start_of_production_body, '|') + 1;
    p->body = malloc(sizeof(production_body) * p->size);

    for(int i=0; i<p->size; ++i) {
        p->body[i].production = malloc(sizeof(char) * 10);
    }

    char* token;

    token = strtok(backup, "|");
    copy_string(p->body[0].production, token);
    for(int i=1; token && i<p->size; ++i){
        token = strtok(NULL, "|");
        copy_string(p->body[i].production, token);
    }
    return p;
}

production* parse_production_from_string(const char* string){
    // Assume our production has the string form A->bB|cC|d;
    production* p = malloc(sizeof(production));
    // Lets first find our left side non-terminal ( A in our example)
    p -> left = string[0];
    production_body_list* b = parse_production_body_from_string(string+3);
    p -> right = b;
    return p;
}

bool is_terminal(char c){
    return !isupper(c);
}

bool is_nonterminal(char c){
    return isupper(c);
}

production* get_production_of_nonterminal(char non_terminal, production **grammar, ssize_t num_productions){
    for(ssize_t i=0; i<num_productions; ++i){
        if(grammar[i]->left == non_terminal) return grammar[i];
    }
    return NULL;
}

production **get_production_from_string_collection(char **grammar, int num_productions) {
    // Create array of pointers to production
    production** p = malloc(sizeof(production) * num_productions);
    // Parse each production
    for(int i=0; i<num_productions; ++i){
        p[i] = parse_production_from_string(grammar[i]);
    }
    return p;
}
