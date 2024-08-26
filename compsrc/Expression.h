#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_
#include "Shared.h"
#include "ASTNode.h"

class Expression:public ASTNode{
public:
    int dataType;
    bool globalBit;
    Expression(int);
    Expression() = default;
    virtual void codeGenerate() = 0;
    virtual void codeGenerateOptional();
    //The codeGenerate() produce a sequence of assembly codes that push the result of this expression to the top of stack memory.
};

class FunctionCall:public Expression{
protected:
    std::string name;
    std::vector<Expression*> arguments;
public:
    FunctionCall(const std::string&,const std::vector<Expression*>&);
    virtual void codeGenerate();
    //virtual void print();
};

class VariableExp:public Expression{
protected:
    std::string name;
public:
    VariableExp(const std::string&);
    virtual void codeGenerate();
    virtual void codeGenerateOptional();
    //virtual void print();
};

class ArrayExp:public Expression{
protected:
    std::string name;
    Expression *index;  
public:
    ArrayExp(const std::string&,Expression*);
    virtual void codeGenerate();
    virtual void codeGenerateOptional();
    //virtual void print();
};

class ConstantExp:public Expression{
protected:
    std::string value;
public:
    ConstantExp(const std::string&,int);
    virtual void codeGenerate();
    //virtual void print();
};

class OperationExp:public Expression{
protected:
    std::string op;
public:
    OperationExp(const std::string&);
    virtual void codeGenerate() = 0;
    //virtual void print() = 0;
};

class UnaryOp:public OperationExp{
    Expression *first;
    static std::unordered_map<std::string,std::function<int(Expression*)>> functionTable;
public:
    UnaryOp(Expression*,const std::string&);
    virtual void codeGenerate();
    //virtual void print();
};

class BinaryOp:public OperationExp{
    Expression *first,*second;
    static std::unordered_map<std::string,std::function<int(Expression*)>> functionTable;
public:
    BinaryOp(Expression*,Expression*,const std::string&);
    virtual void codeGenerate();
    //virtual void print();
};

class TernaryOp:public OperationExp{
    Expression *first,*second,*third;
    static std::unordered_map<std::string,std::function<int(Expression*)>> functionTable;
public:
    TernaryOp(Expression*,Expression*,Expression*,const std::string&);
    virtual void codeGenerate();
    //virtual void print();
};

#endif
