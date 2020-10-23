#include "table.h"
#include "../set.h"
#include "first/first.h"
#include "follow/follow.h"
#include <string.h>

// Representation of each element in our parsing table
typedef struct {
    char non_terminal;
    char input_symbol;
    production* p; // points to NULL if this entry is empty
    int sub_production_index;
}table_entry;

typedef table_entry* table;

int table_size = 0;

table_entry* table_get_entry(table t, char non_terminal, char input_symbol){
    for(int i=0; i<table_size; ++i){
        if(t[i].input_symbol == input_symbol && t[i].non_terminal == non_terminal){
            return &t[i];
        }
    }
}

void table_add(table t, char non_terminal, char input_symbol, production *p, int sub_production_index){
    static int i = 0;
    t[i].non_terminal = non_terminal;
    t[i].input_symbol = input_symbol;
    t[i].p = p;
    t[i].sub_production_index = sub_production_index;
    i = i+1;
}

set get_terminals(production** grammar, ssize_t num_productions){
    set terminals = create_set(10);
    for(ssize_t i=0; i<num_productions; ++i){
        production  *p = grammar[i];
        for(ssize_t j=0; j<p->right->size; ++j){
            char *sub_production = p->right->body[j].production;
            for(int k=0; k< strlen(sub_production); ++k){
                if(is_terminal(sub_production[k])) set_add(terminals, sub_production[k]);
            }
        }
    }
    return terminals;
}

int get_number_of_terminals(production** grammar, ssize_t num_productions){
    set terminals = get_terminals(grammar, num_productions);
    const int num_terminals = get_set_size(terminals);
    set_dealloc(terminals);
    return num_terminals;
}

void create_parsing_table(production** grammar, ssize_t num_productions){
    const int num_non_terminals = num_productions;
    const int num_terminals = get_number_of_terminals(grammar, num_productions);
    const int pt_size = num_non_terminals * num_terminals;
    table_size = pt_size;
    table entries = malloc(sizeof(table_entry) * pt_size);
    for(ssize_t i=0; i<num_productions; ++i){
        production *p = grammar[i];
        const int num_sub_productions = p->right->size;
        for(ssize_t k=0; k<num_sub_productions; ++k){
            production_body sub_production = p->right->body[k];
            // Currently we are examining p.left -> sub_production
            set first = FIRST_string(sub_production.production, grammar, num_productions);

            // Rule 1
            for(ssize_t j=0; j<first->index; ++j){
                const char element = first->elements[j];
                if(is_terminal(element)){
                    table_add(entries, p->left, element, p, k);
                }
            }

            // Rule 2
            if(set_contains(first, '.') != -1){
                // first(alpha) contains epsilon then ...
                set follow = FOLLOW(p->left, grammar, num_productions);
                for(ssize_t j=0; j<follow->index; ++j){
                    const char element = follow->elements[j];
                    if(is_terminal(element)){
                        table_add(entries, p->left, element, p, k);
                    }
                }
            }

        }
    }
}