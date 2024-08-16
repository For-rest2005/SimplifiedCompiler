#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_
#include "Shared.h"
#include <unordered_map>
#include <functional>

class Expression:public ASTNode{
protected:
    static int addrIndex;
    int dataType;
    unsigned int tmpMemAddr;
public:
    Expression(int);
    Expression() = default;
    virtual ~Expression() = default;
    //virtual void print() = 0;
};

class FunctionCall:public Expression{
protected:
    std::string name;
    std::vector<Expression*> arguments;
public:
    FunctionCall(const std::string&,const std::vector<Expression*>&);
    virtual ~FunctionCall();
    //virtual void print();
};

class VariableExp:public Expression{
protected:
    std::string name;
    bool globalBit;
    unsigned int varMemAddr;
public:
    VariableExp(const std::string&);
    //virtual void print();
    // virtual void codeGenerate(VarTable&,FunctionTable&) override;
};

class ArrayExp:public Expression{
protected:
    std::string name;
    bool varType;
    unsigned int varMemAddr;
    Expression *index;  
public:
    ArrayExp(const std::string&,Expression*);
    virtual ~ArrayExp();
    //virtual void print();
    // virtual void codeGenerate(VarTable&,FunctionTable&) override;
};

class ConstantExp:public Expression{
protected:
    std::string value;
public:
    ConstantExp(const std::string&,int);
    //virtual void print();
    // virtual void codeGenerate(VarTable&,FunctionTable&) override;
};

class OperationExp:public Expression{
protected:
    std::string op;
public:
    OperationExp(const std::string&);
    virtual ~OperationExp() = default;
    //virtual void print() = 0;
};

class UnaryOp:public OperationExp{
    Expression *first;
    static std::unordered_map<std::string,std::function<int(Expression*)>> functionTable;
public:
    UnaryOp(Expression*,const std::string&);
    virtual ~UnaryOp();
    //virtual void print();
    // virtual void codeGenerate(VarTable&,FunctionTable&) override{}
};

class BinaryOp:public OperationExp{
    Expression *first,*second;
    static std::unordered_map<std::string,std::function<int(Expression*)>> functionTable;
public:
    BinaryOp(Expression*,Expression*,const std::string&);
    virtual ~BinaryOp();
    //virtual void print();
    // virtual void codeGenerate(VarTable&,FunctionTable&) override{}
};

class TernaryOp:public OperationExp{
    Expression *first,*second,*third;
    static std::unordered_map<std::string,std::function<int(Expression*)>> functionTable;
public:
    TernaryOp(Expression*,Expression*,Expression*,const std::string&);
    virtual ~TernaryOp();
    //virtual void print();
    // virtual void codeGenerate(VarTable&,FunctionTable&) override{}
};

#endif
