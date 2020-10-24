#ifndef PREDICTIVEPARSER_FOLLOW_H
#define PREDICTIVEPARSER_FOLLOW_H

#include "../../datastructure/set.h"
#include "../../datastructure/production.h"

set FOLLOW(char symbol, production** grammar, ssize_t num_productions);

#endif
