#ifndef _STATEMENT_H_
#define _STATEMENT_H_
#include "Shared.h"
class Statement:public ASTNode{
protected:
    Statement *next;
public:
    Statement(Statement*);
    virtual ~Statement();
};

class WhileLoop:public Statement{
protected:
    Statement *statement;
    Expression *condition;
public:

};


class IfCondition:public Statement{
protected:
    Statement *Statement1,*statement2;
    Expression *condition;
public:

};


class GlobalVarDefinition:public Statement{
protected:
    Token key;
    std::vector<>
public:

};

class LocalVarDefinition:public Statement{
protected:

public:

};

class FunctionDefinition:public Statement{
protected:

public:

};

class FunctionDeclaration:public Statement{
protected:

public:

};

class MultiStatement:public Statement{
protected:

public:

};

class ExpressionStatement:public Statement{
protected:

public:
//remember to reset Statement addrIndex
};
#endif