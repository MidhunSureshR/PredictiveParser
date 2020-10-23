#include "first.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>



bool is_epsilon_present(production* p){
    ssize_t len = p->right->size;
    for(ssize_t i=0; i<len; ++i) {
        if(strcmp(p->right->body[i].production, ".") == 0) return true;
    }
    return false;
}

set FIRST(char symbol, production** grammar, ssize_t num_productions){
    set first = create_set(10);
    if(is_terminal(symbol)){
        set_add(first, symbol);
        return first;
    }
    else {
        // Rule 2
        // Find production of symbol
        production *p = get_production_of_nonterminal(symbol, grammar, num_productions);
        // Is symbol->. present ? then add . to set
        if (is_epsilon_present(p)) {
            set_add(first, '.');
        }

        // Rule 3
        for(ssize_t i=0; i<p->right->size; ++i) {
            bool add_epsilon = true;
            const production_body sub_production = p->right->body[i];
            for(int j=0; j<strlen(sub_production.production); ++j){
                set _first = FIRST(sub_production.production[j], grammar, num_productions);
                if(set_contains(_first, '.') == -1) {
                    add_epsilon = false;
                    break;
                }
            }
            if(add_epsilon) set_add(first, '.');
        }

        // For each  X->Y1 Y2 Y3… Yn
        for(ssize_t i=0; i<p->right->size; ++i){
            const production_body sub_production = p->right->body[i];
            const char first_char = sub_production.production[0];
            set _first = FIRST(first_char, grammar, num_productions);
            if(set_contains(_first, '.') != -1 && strlen(sub_production.production) >=2){
                set_remove(_first, '.'); // Remove epsilon
                set_union(_first, FIRST(sub_production.production[1], grammar, num_productions));
                set_union(first, _first);
            }
            else{
                // FIRST(X) = FIRST(Y1)
                set_union(first, _first);
            }
        }
    }
    return first;
}

