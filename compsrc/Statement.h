#ifndef _STATEMENT_H_
#define _STATEMENT_H_
#include "Shared.h"
#include "Expression.h"
#include "ASTNode.h"

class Statement:public ASTNode{
public:
    virtual ~Statement() = default;
    virtual void codeGenerate() = 0;
};

class GlobalStatement:public Statement{
public:
    bool deBit = 0;
    GlobalStatement *next;
    GlobalStatement() = default;
    GlobalStatement(GlobalStatement*);
    virtual ~GlobalStatement();
    virtual void codeGenerate() = 0;
};

class Program:public GlobalStatement{
public:
    Program() = default;
    virtual void codeGenerate();
};

class GlobalVarDeclaration:public GlobalStatement{
protected:
    int dataType;
    std::string varName;
public:
    GlobalVarDeclaration(int,std::string,GlobalStatement*);
    virtual void codeGenerate();
};

class GlobalArrayDeclaration:public GlobalStatement{
protected:
    int dataType;
    std::string varName;
    int size;
public:
    GlobalArrayDeclaration(int,std::string,int,GlobalStatement*);
    virtual void codeGenerate();
};

class FunctionDefinition:public GlobalStatement{
protected:
    int returnDataType;
    std::vector<std::pair<int,std::string>> arguments;// type and name
    std::string funName;
    Statement *body;
public:
    FunctionDefinition(int,std::string,std::vector<std::pair<int,std::string>>&,Statement*,GlobalStatement*);
    virtual void codeGenerate();
};

class FunctionDeclaration:public GlobalStatement{
protected:
    int returnDataType;
    std::vector<std::pair<int,std::string>> arguments;// type and name
    std::string funName;
public:
    FunctionDeclaration(int,std::string,std::vector<std::pair<int,std::string>>&,GlobalStatement*);
    virtual void codeGenerate();
};

class WhileStatement:public Statement{
protected:
    Statement *body;
    Expression *condition;
public:
    WhileStatement(Expression*,Statement*);
    virtual void codeGenerate();
};

class IfStatement:public Statement{
protected:
    Statement *body1,*body2;
    Expression *condition;
public:
    IfStatement(Expression*,Statement*,Statement*);
    virtual void codeGenerate();
};

class LocalVarDeclaration:public Statement{
protected:
    int dataType;
    std::string varName;
public:
    LocalVarDeclaration(int,std::string);
    virtual void codeGenerate();
};

class LocalArrayDeclaration:public Statement{
protected:
    int dataType;
    std::string varName;
    int size;
public:
    LocalArrayDeclaration(int,std::string,int);
    virtual void codeGenerate();
};

class Scope:public Statement{
protected:
    std::vector<Statement*> body;
public:
    Scope() = default;
    void push(Statement*);
    virtual void codeGenerate();
};

class ExpStatement:public Statement{
protected:
    Expression *body;
public:
    ExpStatement(Expression*);
    virtual void codeGenerate();
//remember to reset Statement addrIndex
};

class ReturnStatement:public Statement{
protected:
    Expression *value;
public:
    ReturnStatement(Expression*);
    virtual void codeGenerate();
};

class ContinueStatement:public Statement{
public:
    virtual void codeGenerate();
};

class BreakStatement:public Statement{
public:
    virtual void codeGenerate();
};

class ReadStatement:public Statement{
protected:
    Expression *addr;
public:
    ReadStatement(Expression*);
    virtual void codeGenerate();
};

class PrintStatement:public Statement{
protected:
    Expression *value;
public:
    PrintStatement(Expression*);
    virtual void codeGenerate();
};

class PutcharStatement:public Statement{
protected:
    Expression *value;
public:
    PutcharStatement(Expression*);
    virtual void codeGenerate();
};

#endif