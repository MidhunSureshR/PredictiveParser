#include "production.h"
#include <stdio.h>
#include <stdlib.h>
#include "test.h"

char** get_grammar_from_user(int num_productions){
    char** grammar = malloc(sizeof(int *) * num_productions);
    for(int i=0; i < num_productions; ++i){
        grammar[i] = malloc(sizeof(char) * 100);
        scanf("%s", grammar[i]);
    }
    return grammar;
}

int get_productions_count(){
    int num_productions;
    scanf("%d", &num_productions);
    return num_productions;
}

void run_tests(){
    // char grammar_string[5][50] = {"E->TA", "A->+TA|.", "T->FB", "B->*FB|.", "F->(E)|i"};
    // char grammar_string[6][50] = {"S->aBDh", "B->cC", "C->bC|.", "D->EF", "E->g|.", "F->f|."};
    char grammar_string[4][50] = {"S->ACB|Cbb|Ba", "A->da|BC", "B->g|.", "C->h|."};
    test_first(grammar_string, 4);
    printf("----------------------------------------\n");
    test_follow(grammar_string, 4);
}

int main() {
    printf("Predictive Parser\n");
/*
    printf("Enter number of productions:");
    const int num_productions = get_productions_count();
    char **grammar = get_grammar_from_user(num_productions);

    // Create array of pointers to production
    production** p = malloc(sizeof(production) * num_productions);
    // Parse each production
    for(int i=0; i<num_productions; ++i){
        p[i] = parse_production_from_string(grammar[i]);
    }
    for(int i=0; i<num_productions; ++i){
        print_production(p[i]);
    }
*/
    run_tests();
    return 0;
}
