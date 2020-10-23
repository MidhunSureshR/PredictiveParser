#ifndef PREDICTIVEPARSER_FOLLOW_H
#define PREDICTIVEPARSER_FOLLOW_H

#include "../../set.h"
#include "../../production.h"

set FOLLOW(char symbol, production** grammar, ssize_t num_productions);

#endif
