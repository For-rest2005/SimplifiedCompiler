#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_
#include "Shared.h"
#include <unordered_map>
#include <functional>

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
protected:
    std::string op;
public:
    OperationExp(const std::string&);
};

class UnaryOp:public OperationExp{
    Expression *first;
    static std::unordered_map<std::string,std::function<int(Expression*)>> functionTable;
public:
    // virtual void codeGenerate(VarTable&,FunctionTable&) override{}
};

class BinaryOp:public OperationExp{
    Expression *first,*second;
    static std::unordered_map<std::string,std::function<int(Expression*)>> functionTable;
public:
    BinaryOp(Expression*,Expression*,const std::string&);
    // virtual void codeGenerate(VarTable&,FunctionTable&) override{}
};

class TernaryOp:public OperationExp{
    Expression *first,*second,*third;
    static std::unordered_map<std::string,std::function<int(Expression*)>> functionTable;
public:
    TernaryOp(Expression*,Expression*,Expression*,const std::string&);
    // virtual void codeGenerate(VarTable&,FunctionTable&) override{}
};

#endif
