cmake_minimum_required(VERSION 3.17)
project(PredictiveParser C)

set(CMAKE_C_STANDARD 11)

add_executable(PredictiveParser parser.c production.c production.h helper.c helper.h test.c test.h calculations.c calculations.h set.c set.h)