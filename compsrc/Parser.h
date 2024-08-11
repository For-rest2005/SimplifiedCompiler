#ifndef _PARSER_H_
#define _PARSER_H_

#include "Shared.h"

Statement* parser();
Statement* getStatement();
Expression* pareseExp(std::vector<Token> exp);


#endif