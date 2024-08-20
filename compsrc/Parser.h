#ifndef _PARSER_H_
#define _PARSER_H_

#include "Shared.h"

int getDataType();
Statement* getStatementGlobal();
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