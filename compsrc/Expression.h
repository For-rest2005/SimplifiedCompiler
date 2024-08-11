#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_
#include "Shared.h"
#include <unordered_map>

class Expression:public ASTNode{
protected:
    static int addrIndex;
public:
    int dataType;
    unsigned int tmpMemAddr;
};

class VariableExp:public Expression{
protected:
    std::string identifierName;
    bool globalBit;
    unsigned int varMemAddr;
public:
    // virtual void codeGenerate(VarTable&,FunctionTable&) override;
};

class ArrayVariableExp:public Expression{
protected:
    std::string identifierName;
    bool varType;
    unsigned int varMemAddr;
    Expression *index;  
public:
    // virtual void codeGenerate(VarTable&,FunctionTable&) override;
};

class ConstantExp:public Expression{
public:
    std::string value;
    // virtual void codeGenerate(VarTable&,FunctionTable&) override;
};

class OperationExp:public Expression{
public:
    std::string opType;
};

class UnaryOp:public OperationExp{
    Expression *first;
    static std::unordered_map<std::string,std::function<int(Expression*)>> functionTable;
public:
    // virtual void codeGenerate(VarTable&,FunctionTable&) override{}
};

class binaryOp:public OperationExp{
    Expression *first,*second;
    static std::unordered_map<std::string,std::function<int(Expression*)>> functionTable;
public:
    // virtual void codeGenerate(VarTable&,FunctionTable&) override{}
};

class ternaryOp:public OperationExp{
    Expression *first,*second,*third;
    static std::unordered_map<std::string,std::function<int(Expression*)>> functionTable;
public:
    // virtual void codeGenerate(VarTable&,FunctionTable&) override{}
};

#endif
