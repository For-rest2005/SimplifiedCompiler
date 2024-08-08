#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_
#include "ASTNode.h"
#include <unordered_map>
#include <functional>

class Expression:public ASTNode{
public:
    int dataType;
    unsigned int tmpMemAddr;
};

class VariableExp:public Expression{
protected:
    std::string identifierName;  
public:
    virtual void codeGenerate() override;
};

class ArrayVariableExp:public Expression{
protected:
    std::string identifierName;
    Expression *index;  
public:
    virtual void codeGenerate() override;
};

class OperationExp:public Expression{
public:
    std::string opType;
};

class UnaryOp:public OperationExp{
    Expression *first;
    static std::unordered_map<std::string,std::function<int(Expression*)>> functionTable;
public:
    virtual void codeGenerate() override{}
};

class binaryOp:public OperationExp{
    Expression *first,*second;
    static std::unordered_map<std::string,std::function<int(Expression*)>> functionTable;
public:
    virtual void codeGenerate() override{}
};

class ternaryOp:public OperationExp{
    Expression *first,*second,*third;
    static std::unordered_map<std::string,std::function<int(Expression*)>> functionTable;
public:
    virtual void codeGenerate() override{}
};

#endif
