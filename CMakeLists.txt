cmake_minimum_required(VERSION 3.17)
project(PredictiveParser C)

set(CMAKE_C_STANDARD 11)

add_executable(PredictiveParser parser.c production.c production.h helper.c helper.h test.c test.h calculation/first/first.c calculation/first/first.h set.c set.h calculation/follow/follow.c calculation/follow/follow.h calculation/table.c calculation/table.h p_parser.c p_parser.h)