#ifndef PREDICTIVEPARSER_FIRST_H
#define PREDICTIVEPARSER_FIRST_H

#include "../../set.h"
#include "../../production.h"
set FIRST(char, production**, ssize_t);
set FIRST_string(char *string, production** grammar, ssize_t num_productions);

#endif
