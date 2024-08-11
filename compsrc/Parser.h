#ifndef _PARSER_H_
#define _PARSER_H_

#include "Shared.h"
#include "Expression.h"
#include "Statement.h"

Statement* parser();
Statement* getStatementGlobal();
Statement* getStatementLocal();
Expression* parserExp(std::vector<Token> &exp,int l, int r);


#endif