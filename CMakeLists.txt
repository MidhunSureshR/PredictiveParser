cmake_minimum_required(VERSION 3.17)
project(PredictiveParser C)

set(CMAKE_C_STANDARD 11)

add_executable(PredictiveParser parser.c datastructure/production.c datastructure/production.h helpers/string_helper.c helpers/string_helper.h unit_tests/test.c unit_tests/test.h calculation/first/first.c calculation/first/first.h datastructure/set.c datastructure/set.h calculation/follow/follow.c calculation/follow/follow.h calculation/parsing_table/table.c calculation/parsing_table/table.h predictive_parser/p_parser.c predictive_parser/p_parser.h datastructure/stack.c datastructure/stack.h)