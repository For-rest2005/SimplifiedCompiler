#include "Statement.h"

GlobalVarDeclaration::GlobalVarDeclaration(int _dataType,std::string _varName,Statement *_next):dataType(_dataType),varName(_varName),next(_next){}
GlobalVarDeclaration::~GlobalVarDeclaration(){delete next;}

GlobalArrayDeclaration::GlobalArrayDeclaration(int _dataType,std::string _varName,int _size,Statement *_next):
    dataType(_dataType),varName(_varName),size(_size),next(_next){}
GlobalArrayDeclaration::~GlobalArrayDeclaration(){delete next;}

FunctionDefinition::FunctionDefinition(int _returnDataType,std::string _funName,std::vector<std::pair<int,std::string>> &_arguments,Statement*_body,Statement*_next)
:returnDataType(_returnDataType),funName(_funName),arguments(_arguments),body(_body),next(_next){}
FunctionDefinition::~FunctionDefinition(){delete body,next;}

FunctionDeclaration::FunctionDeclaration(int _returnDataType,std::string _funName,std::vector<std::pair<int,std::string>> &_arguments,Statement*_next)
:returnDataType(_returnDataType),funName(_funName),arguments(_arguments),next(_next){}
FunctionDeclaration::~FunctionDeclaration(){delete next;}

WhileStatement::WhileStatement(Expression *_condition,Statement *_body):condition(_condition),body(_body){}
WhileStatement::~WhileStatement(){delete body,condition;}

IfStatement::IfStatement(Expression *_condition,Statement *_body1,Statement *_body2):condition(_condition),body1(_body1),body2(_body2){}
IfStatement::~IfStatement(){delete condition,body1,body2;}

void Scope::push(Statement *statement){body.push_back(statement);}
Scope::~Scope(){
    for(auto each:body){
        delete each;
    }
}

ExpStatement::ExpStatement(Expression *_body):body(_body){}
ExpStatement::~ExpStatement(){delete body;}

LocalArrayDeclaration::LocalArrayDeclaration(int _dataType,std::string _varName,int _size):dataType(_dataType),varName(_varName),size(_size){}

LocalVarDeclaration::LocalVarDeclaration(int _dataType,std::string _varName):dataType(_dataType),varName(_varName){}

ReturnStatement::ReturnStatement(Expression *_value):value(_value){}
ReturnStatement::~ReturnStatement(){delete value;}