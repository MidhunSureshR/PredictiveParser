#include <string.h>
#include <stdio.h>
#include "test.h"
#include "set.h"
#include "calculation/first/first.h"
#include "calculation/follow/follow.h"

#define num_cases 3
#define first_cases 5

bool test_set_add(){
    set s = create_set(5);
    set_add(s, 'A');
    set_add(s, 'B');
    set_add(s, 'C');
    set_add(s, 'A');
    print_set(s);
}

bool test_set_remove(){
    set s = create_set(5);
    set_add(s, 'A');
    set_add(s, 'B');
    set_add(s, 'C');
    set_add(s, 'D');
    set_add(s, 'E');
    set_remove(s, 'C');
    print_set(s);
}

bool test_set_union(){
    set a,b;
    a = create_set(4);
    b = create_set(5);
    set_add(a, 'A');
    set_add(a, 'B');
    set_add(b, 'C');
    set_add(b, 'D');
    set_union(a, b);
    print_set(a);
};

bool test_input_parsing(){
    char test_cases[num_cases][50] = {"A->bB|cD|D", "B->.", "D->x|y|z|w"};
    production** p = malloc(sizeof(production) * num_cases);
    char string[100];
    for(int i=0; i<num_cases; ++i){
        p[i] = parse_production_from_string(test_cases[i]);
    }
    for(int i=0; i<num_cases; ++i){
        get_production_as_string(string, p[i]);
        if(strcmp(string, test_cases[i]) == 0) printf("\tTest case {%d} : Passed ✔\n", i+1);
        else {
            printf("\tTest case {%d} : Failed ✖\n", i+1);
            printf("\t\tExpected = %s\n\t\tFound = %s\n", test_cases[i], string);
        }
    }
    return true;
}

bool test_first(char (*grammar_string)[50], int len){
    /*
    E  -> TA
    A -> +TA|Є
    T  -> FB
    B -> *FB | Є
    F  -> (E)| id
     */
    //char grammar_string[len][50] = {"E->TA", "A->+TA|.", "T->FB", "B->*FB|.", "F->(E)|i"};
    production** p = malloc(sizeof(production) * len);
    for(int i=0; i<len; ++i){
        p[i] = parse_production_from_string(grammar_string[i]);
    }
    for(int i=0; i<len; ++i){
        const char symbol = p[i]->left;
        set first = FIRST(symbol, p, len);
        printf("FIRST(%c) = ", symbol);
        print_set(first);
    }
    return true;
}

bool test_follow(char (*grammar_string)[50], int len){
    /*
    E  -> TA
    A -> +TA|Є
    T  -> FB
    B -> *FB | Є
    F  -> (E)| id
     */
    //char grammar_string[first_cases][50] = {"E->TA", "A->+TA|.", "T->FB", "B->*FB|.", "F->(E)|i"};
    production** p = malloc(sizeof(production) * len);
    for(int i=0; i<len; ++i){
        p[i] = parse_production_from_string(grammar_string[i]);
    }
    for(int i=0; i<len; ++i){
        const char symbol = p[i]->left;
        set follow = FOLLOW(symbol, p, len);
        printf("FOLLOW(%c) = ", symbol);
        print_set(follow);
    }
//    set follow = FOLLOW('C', p, len);
//    print_set(follow);
    return true;
}
