#include "calculations.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bool is_terminal(char c){
    return !isupper(c);
}

production* get_production_of_nonterminal(char non_terminal, production **grammar, ssize_t num_productions){
    for(ssize_t i=0; i<num_productions; ++i){
        if(grammar[i]->left == non_terminal) return grammar[i];
    }
    return NULL;
}

bool is_epsilon_present(production* p){
    ssize_t len = p->right->size;
    for(ssize_t i=0; i<len; ++i) {
        if(strcmp(p->right->body[i].production, ".") == 0) return true;
    }
    return false;
}

set FIRST(char symbol, production** grammar, ssize_t num_productions){
    printf("Called FIRST symbol = %c\n", symbol);
    set first = create_set(10);
    if(is_terminal(symbol)){
        set_add(first, symbol);
        return first;
    }
    else {
        // Find production of symbol
        production *p = get_production_of_nonterminal(symbol, grammar, num_productions);
        // Is symbol->. present ? then add . to set
        if (is_epsilon_present(p)) {
            set_add(first, '.');
        }

        // Rule two
        ssize_t num_bodies = p->right->size;
        for (ssize_t i = 0; i < num_bodies; ++i) {
            int j = 0;
            char s;
            while (true) {
                s = p->right->body[i].production[j];
                set _first = FIRST(s, grammar, num_productions);
                set_union(first, _first);
                printf("Before removing . : ");
                print_set(first);
                if (set_contains(_first, '.') != -1 && !is_set_singleton(_first)) {
                    printf("\tIn if loop\n");
                    j++;
                    set_remove(first, '.');
                    printf("After removing . : ");
                    print_set(first);
                } else break;
            }
        }

        // Rule 3
        for (ssize_t i = 0; i < num_bodies; ++i) {
            bool add_epsilon = true;
            for(ssize_t j=0; j < strlen(p->right->body[i].production); ++j){
                char s = p->right->body[i].production[j];
                set _first = FIRST(s, grammar, num_productions);
                if(!set_contains(_first, '.')) {
                    add_epsilon = false;
                    break;
                }
            }
            if(add_epsilon) set_add(first, '.');
        }
    }
    return first;
}