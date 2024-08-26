#include "Statement.h"

GlobalVarDeclaration::GlobalVarDeclaration(int _dataType,std::string _varName,GlobalStatement *_next):dataType(_dataType),varName(_varName),GlobalStatement(_next){}

GlobalArrayDeclaration::GlobalArrayDeclaration(int _dataType,std::string _varName,int _size,GlobalStatement *_next):
    dataType(_dataType),varName(_varName),size(_size),GlobalStatement(_next){}

FunctionDefinition::FunctionDefinition(int _returnDataType,std::string _funName,std::vector<std::pair<int,std::string>> &_arguments,Statement*_body,GlobalStatement*_next)
:returnDataType(_returnDataType),funName(_funName),arguments(_arguments),body(_body),GlobalStatement(_next){}

FunctionDeclaration::FunctionDeclaration(int _returnDataType,std::string _funName,std::vector<std::pair<int,std::string>> &_arguments,GlobalStatement*_next)
:returnDataType(_returnDataType),funName(_funName),arguments(_arguments),GlobalStatement(_next){}

WhileStatement::WhileStatement(Expression *_condition,Statement *_body):condition(_condition),body(_body){}

IfStatement::IfStatement(Expression *_condition,Statement *_body1,Statement *_body2):condition(_condition),body1(_body1),body2(_body2){}

void Scope::push(Statement *statement){body.push_back(statement);}

GlobalStatement::GlobalStatement(GlobalStatement* _next):next(_next){}
GlobalStatement::~GlobalStatement(){delete next;}

ExpStatement::ExpStatement(Expression *_body):body(_body){}

LocalArrayDeclaration::LocalArrayDeclaration(int _dataType,std::string _varName,int _size):dataType(_dataType),varName(_varName),size(_size){}

LocalVarDeclaration::LocalVarDeclaration(int _dataType,std::string _varName):dataType(_dataType),varName(_varName){}

ReturnStatement::ReturnStatement(Expression *_value):value(_value){}

ReadStatement::ReadStatement(Expression *_addr):addr(_addr){}

PutcharStatement::PutcharStatement(Expression *_value):value(_value){}

PrintStatement::PrintStatement(Expression *_value):value(_value){}

