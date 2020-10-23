#include "follow.h"
#include "../first/first.h"
#include <string.h>
#include <stdio.h>

set FOLLOW(char symbol, production** grammar, ssize_t num_productions){
    // FOLLOW is defined only for non-terminals
    /*
    FOLLOW(S) = { $ } where S is the starting Non-Terminal
    */
    set follow = create_set(10);
    char S = grammar[0]->left;
    if(symbol == S){
        set_add(follow, '$');
    }
   for(ssize_t i=0; i<num_productions; ++i){
       production* p = grammar[i];
       for(ssize_t j=0; j<p->right->size; ++j){
           production_body sub_production = p->right->body[j];
           const int strlen_production = strlen(sub_production.production);
           for(int k=0; k<strlen_production; ++k){
               if(sub_production.production[k] == symbol){
                  if(k == strlen_production-1){
                      // symbol is last character in the production
                      if(p->left != symbol) { // Eliminate nasty infinite recursion
                          set _follow = FOLLOW(p->left, grammar, num_productions);
                          set_union(follow, _follow);
                      }
                  }
                  else{
                      // there are characters to the right of symbol
                      set _first = FIRST(sub_production.production[k+1], grammar, num_productions);
                      bool set_contains_epsilon = set_contains(_first, '.') != -1;
                      set_remove(_first, '.');
                      set_union(follow, _first);
                      if(set_contains_epsilon){
                          // FIRST(next_char) contains epsilon
                          set _follow = FOLLOW(p->left, grammar, num_productions);
                          set_union(follow, _follow);
                      }
                  }
               }
           }
       }
   }
   return follow;
}