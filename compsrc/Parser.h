#ifndef _PARSER_H_
#define _PARSER_H_

#include "Shared.h"
#include "Statement.h"
#include "Lexer.h"
#include "Expression.h"

int getDataType();
GlobalStatement* getStatementGlobal();
Statement* getStatementLocal();
Expression* parseExp();

class binaryParse{
private:
    std::function<Expression*()> next;
    std::vector<std::string> op;
public:
    binaryParse(const std::vector<std::string>&,std::function<Expression*()>);
    bool checkOp(std::string);
    Expression *operator()();
};

#endif