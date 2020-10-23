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
    test_input_parsing();
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
    //run_tests();
   //test_set_union();
   //test_set_remove();
   //test_set_add();
   test_set_union();
    //   test_first();
    test_follow();
    return 0;
}
