#include"Expression.h"

OperationExp::OperationExp(const std::string &_op):op(_op){}

BinaryOp::BinaryOp(Expression *_first,Expression *_second,const std::string &_op):first(_first),second(_second),OperationExp(_op){}