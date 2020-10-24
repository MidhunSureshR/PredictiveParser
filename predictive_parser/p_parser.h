#ifndef PREDICTIVEPARSER_P_PARSER_H
#define PREDICTIVEPARSER_P_PARSER_H

#include "../calculation/parsing_table/table.h"
#include "../datastructure/production.h"

void predictive_parse(const char* string, table parsing_table, production** grammar);

#endif
