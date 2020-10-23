#ifndef PREDICTIVEPARSER_TABLE_H
#define PREDICTIVEPARSER_TABLE_H

#include "../production.h"

// Representation of each element in our parsing table
typedef struct {
    char non_terminal;
    char input_symbol;
    production* p; // points to NULL if this entry is empty
    int sub_production_index;
}table_entry;

typedef table_entry* table;

table create_parsing_table(production** grammar, ssize_t num_productions);
table_entry* table_get_entry(table t, char non_terminal, char input_symbol);
void print_table(table t);

#endif
