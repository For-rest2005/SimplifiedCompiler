#ifndef _STATEMENT_H_
#define _STATEMENT_H_
#include "Shared.h"
#include "Expression.h"
#include <vector>
class Statement:public ASTNode{
public:
    virtual ~Statement() = default;
    virtual void codeGenerate();
};

class WhileStatement:public Statement{
protected:
    Statement *body;
    Expression *condition;
public:
    WhileStatement(Expression*,Statement*);
    virtual ~WhileStatement();
    virtual void codeGenerate();
};

class IfStatement:public Statement{
protected:
    Statement *body1,*body2;
    Expression *condition;
public:
    IfStatement(Expression*,Statement*,Statement*);
    virtual ~IfStatement();
    virtual void codeGenerate();
};


class GlobalVarDeclaration:public Statement{
protected:
    int dataType;
    Statement *next;
    std::string varName;
public:
    GlobalVarDeclaration(int,std::string,Statement*);
    virtual ~GlobalVarDeclaration();
    virtual void codeGenerate();
};

class GlobalArrayDeclaration:public Statement{
protected:
    int dataType;
    Statement *next;
    std::string varName;
    int size;
public:
    GlobalArrayDeclaration(int,std::string,int,Statement*);
    virtual ~GlobalArrayDeclaration();
    virtual void codeGenerate();
};

class LocalVarDeclaration:public Statement{
protected:
    int dataType;
    std::string varName;
public:
    LocalVarDeclaration(int,std::string);
    virtual ~LocalVarDeclaration() = default;
    virtual void codeGenerate();
};

class LocalArrayDeclaration:public Statement{
protected:
    int dataType;
    std::string varName;
    int size;
public:
    LocalArrayDeclaration(int,std::string,int);
    virtual ~LocalArrayDeclaration() = default;
    virtual void codeGenerate();
};

class FunctionDefinition:public Statement{
protected:
    int returnDataType;
    std::vector<std::pair<int,std::string>> arguments;// type and name
    std::string funName;
    Statement *body;
    Statement *next;
public:
    FunctionDefinition(int,std::string,std::vector<std::pair<int,std::string>>&,Statement*,Statement*);
    virtual ~FunctionDefinition();
    virtual void codeGenerate();
};

class FunctionDeclaration:public Statement{
protected:
    int returnDataType;
    std::vector<std::pair<int,std::string>> arguments;// type and name
    std::string funName;
    Statement *next;
public:
    FunctionDeclaration(int,std::string,std::vector<std::pair<int,std::string>>&,Statement*);
    virtual ~FunctionDeclaration();
    virtual void codeGenerate();
};

class Scope:public Statement{
protected:
    std::vector<Statement*> body;
public:
    Scope() = default;
    void push(Statement*);
    virtual ~Scope();
    virtual void codeGenerate();
};

class ExpStatement:public Statement{
protected:
    Expression *body;
public:
    ExpStatement(Expression*);
    virtual ~ExpStatement();
    virtual void codeGenerate();
//remember to reset Statement addrIndex
};

class ReturnStatement:public Statement{
protected:
    Expression *value;
public:
    ReturnStatement(Expression*);
    virtual ~ReturnStatement();
    virtual void codeGenerate();
};

class ContinueStatement:public Statement{
public:
    virtual ~ContinueStatement() = default;
    virtual void codeGenerate();
};

class BreakStatement:public Statement{
public:
    virtual ~BreakStatement() = default;
    virtual void codeGenerate();
};

class ReadStatement:public Statement{
protected:
    Expression *addr;
public:
    ReadStatement(Expression*);
    virtual ~ReadStatement();
    virtual void codeGenerate();
};

class PrintStatement:public Statement{
protected:
    Expression *value;
public:
    PrintStatement(Expression*);
    virtual ~PrintStatement();
    virtual void codeGenerate();
};

class PutcharStatement:public Statement{
protected:
    Expression *value;
public:
    PutcharStatement(Expression*);
    virtual ~PutcharStatement();
    virtual void codeGenerate();
};

#endif