#include"Expression.h"

Expression::Expression(int _dataType):dataType(_dataType){}
void Expression::codeGenerateOptional(){}

OperationExp::OperationExp(const std::string &_op):op(_op){}

UnaryOp::UnaryOp(Expression *_first,const std::string &_op):first(_first),OperationExp(_op){}

BinaryOp::BinaryOp(Expression *_first,Expression *_second,const std::string &_op):first(_first),second(_second),OperationExp(_op){}

TernaryOp::TernaryOp(Expression *_first,Expression *_second,Expression *_third,const std::string &_op):first(_first),second(_second),third(_third),OperationExp(_op){}

FunctionCall::FunctionCall(const std::string &_name,const std::vector<Expression*> &_arguments):name(_name),arguments(_arguments){}

ConstantExp::ConstantExp(const std::string &_value,int _dataType):value(_value),Expression(_dataType){}

ArrayExp::ArrayExp(const std::string &_name,Expression *_index):name(_name),index(_index){}

VariableExp::VariableExp(const std::string &_name):name(_name){}