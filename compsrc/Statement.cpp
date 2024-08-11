#include "Statement.h"

GlobalVarDeclaration::GlobalVarDeclaration(int _dataType,std::string _varName,Statement *_next):dataType(_dataType),varName(_varName),next(_next){}

GlobalArrayDeclaration::GlobalArrayDeclaration(int _dataType,std::string _varName,unsigned int _size,Statement *_next):
    dataType(_dataType),varName(_varName),size(_size),next(_next){}

FunctionDefinition::FunctionDefinition(int _returnDataType,std::string _funName,std::vector<std::pair<int,std::string>> &_arguement,Statement*_body,Statement*_next)
:returnDataType(_returnDataType),funName(_funName),arguement(_arguement),body(_body),next(_next){}

FunctionDeclaration::FunctionDeclaration(int _returnDataType,std::string _funName,std::vector<std::pair<int,std::string>> &_arguement,Statement*_next)
:returnDataType(_returnDataType),funName(_funName),arguement(_arguement),next(_next){}

WhileLoop::WhileLoop(Expression *_condition,Statement *_body):condition(_condition),body(_body){}

IfCondition::IfCondition(Expression *_condition,Statement *_body1,Statement *_body2):condition(_condition),body1(_body1),body2(_body2){}

void Scope::push(Statement *statement){body.push_back(statement);}

ExpStatement::ExpStatement(Expression *_body):body(_body){}