#ifndef _STATEMENT_H_
#define _STATEMENT_H_
#include"ASTNode.h"
class Statement:public ASTNode{
protected:
    Statement *next;
public:
    virtual ~Statement();
};

class WhileLoop:public Statement{
protected:

public:

};


class If:public Statement{
protected:

public:

};


class GlobalInt:public Statement{
protected:

public:

};

class LocalInt:public Statement{
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

};

#endif