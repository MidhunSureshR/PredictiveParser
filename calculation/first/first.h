#ifndef PREDICTIVEPARSER_FIRST_H
#define PREDICTIVEPARSER_FIRST_H

#include "../../datastructure/set.h"
#include "../../datastructure/production.h"
set FIRST(char, production**, ssize_t);
set FIRST_string(char *string, production** grammar, ssize_t num_productions);

#endif
