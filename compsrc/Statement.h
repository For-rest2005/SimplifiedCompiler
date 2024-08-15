#ifndef _STATEMENT_H_
#define _STATEMENT_H_
#include "Shared.h"
#include "Expression.h"
#include <vector>
class Statement:public ASTNode{
public:
    virtual ~Statement() = 0;
};

class WhileLoop:public Statement{
protected:
    Statement *body;
    Expression *condition;
public:
    WhileLoop(Expression*,Statement*);
    virtual ~WhileLoop();
};

class IfCondition:public Statement{
protected:
    Statement *body1,*body2;
    Expression *condition;
public:
    IfCondition(Expression*,Statement*,Statement*);
    virtual ~IfCondition();
};


class GlobalVarDeclaration:public Statement{
protected:
    int dataType;
    Statement *next;
    std::string varName;
public:
    GlobalVarDeclaration(int,std::string,Statement*);
    virtual ~GlobalVarDeclaration();
};

class GlobalArrayDeclaration:public Statement{
protected:
    int dataType;
    Statement *next;
    std::string varName;
    unsigned int size;
public:
    GlobalArrayDeclaration(int,std::string,unsigned int,Statement*);
    virtual ~GlobalArrayDeclaration();
};

class LocalVarDeclaration:public Statement{
protected:
    int dataType;
    std::string varName;
public:
    LocalVarDeclaration(int,std::string);
    virtual ~LocalVarDeclaration();
};

class LocalArrayDeclaration:public Statement{
protected:
    int dataType;
    std::string varName;
    unsigned int size;
public:
    LocalArrayDeclaration(int,std::string,unsigned int)
};

class FunctionDefinition:public Statement{
protected:
    int returnDataType;
    std::vector<std::pair<int,std::string>> arguement;// type and name
    std::string funName;
    Statement *body;
    Statement *next;
public:
    FunctionDefinition(int,std::string,std::vector<std::pair<int,std::string>>&,Statement*,Statement*);
    virtual ~FunctionDefinition();
};

class FunctionDeclaration:public Statement{
protected:
    int returnDataType;
    std::vector<std::pair<int,std::string>> arguement;// type and name
    std::string funName;
    Statement *next;
public:
    FunctionDeclaration(int,std::string,std::vector<std::pair<int,std::string>>&,Statement*);
    virtual ~FunctionDeclaration();
};

class Scope:public Statement{
protected:
    std::vector<Statement*> body;
public:
    Scope() = default;
    void push(Statement*);
    virtual ~Scope();
};

class ExpStatement:public Statement{
protected:
    Expression *body;
public:
    ExpStatement(Expression*);
    virtual ~ExpStatement();
//remember to reset Statement addrIndex
};
#endif