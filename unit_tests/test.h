#ifndef PREDICTIVEPARSER_TEST_H
#define PREDICTIVEPARSER_TEST_H
#include <stdbool.h>
#include "../datastructure/production.h"

bool test_first(char (*grammar_string)[50], int len);
bool test_input_parsing();
bool test_set_union();
bool test_set_remove();
bool test_set_add();
bool test_follow(char (*grammar_string)[50], int len);

#endif
