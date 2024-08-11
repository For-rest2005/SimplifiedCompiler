#include "Parser.h"

static std::unordered_set<std::string> typeIndicator = {"int","void","int*"};
static std::unordered_map<std::string,int> reDataType = {{"int",INT},{"void",VOID},{"int*",INTPOINTER}};

int getDataType(){
    Token keyword = getToken();
    Token optional = getToken();
    if(keyword.type() == ENDPOINT) return -1;
    std::string _str = keyword.value()+optional.value();
    if(typeIndicator.find(_str) != typeIndicator.end())
        return reDataType[_str];
    unGetToken(optional);
    if(typeIndicator.find(_str) != typeIndicator.end())
        return reDataType[keyword.value()];
    unGetToken(keyword);
    return -2;
}

Statement* getStatementGlobal(){
    int dataType = getDataType();
    if(dataType == -1) return nullptr;
    if(dataType == -2) errorReport("Invalid type indicator");
    Statement *curStatement;
    Token name = getToken();
    if(name.type() != IDENTIFIER)
        errorReport("Invalid function or varible name");
    Token op = getToken();
    if(op.value() == ";"){
        curStatement = new GlobalVarDeclaration(dataType,name.value(),getStatementGlobal());
    }
    else if(op.value() == "["){
        int _size = getToken().toInteger();
        skipTokens(2);
        curStatement = new GlobalArrayDeclaration(dataType,name.value(),_size,getStatementGlobal());
    }
    else if(op.value() == "("){
        std::vector<std::pair<int,std::string>> typeNameList;
        int argVarType;
        while(true){
            argVarType = getDataType();
            if(argVarType == -2){
                if(getToken().value() != ")")
                    errorReport("Mismatch parenthese");
                break;
            }
            Token varName;
            varName = getToken();
            if(varName.type() != IDENTIFIER)
                unGetToken(varName);
            typeNameList.push_back({argVarType,varName.value()});
        }
        op = getToken();
        if(op.value() == "{"){
            unGetToken(op);
            Statement *body = getStatementLocal();
            curStatement = new FunctionDefinition(dataType,name.value(),typeNameList,body,getStatementGlobal());
        }else if(op.type() == SEMICOLON){
            curStatement = new FunctionDeclaration(dataType,name.value(),typeNameList,getStatementGlobal());
        }else{
            errorReport("Error function definition");
        }
    }
    else errorReport("Error declaration");
    return curStatement;
}

void getExp(std::vector<Token> &condition,const std::string& _str){
    Token curToken;
    skipTokens();
    while((curToken=getToken()).value() != _str)
        condition.push_back(curToken);
}

Statement* getStatementLocal(){
    Token keyword = getToken();
    std::string _str = keyword.value();
    Statement *curStatement;
    Token bufferToken;
    if(_str == "while"){
        std::vector<Token> condition;
        getExp(condition,")");
        curStatement = new WhileLoop(parserExp(condition,0,(int)condition.size()-1),getStatementLocal());
    }
    else if(_str == "if"){
        std::vector<Token> condition;
        getExp(condition,")");
        curStatement = getStatementLocal();
        bufferToken = getToken();
        if(bufferToken.value() == "else")
            curStatement = new IfCondition(parserExp(condition,0,(int)condition.size()-1),curStatement,getStatementLocal());
        else{
            unGetToken(bufferToken);
            curStatement = new IfCondition(parserExp(condition,0,(int)condition.size()-1),curStatement,nullptr);
        }
    }
    else if(_str == "{"){
        Scope *scope;
        scope = new Scope();
        while((bufferToken = getToken()).value() != "}"){
            unGetToken(bufferToken);
            scope->push(getStatementLocal());
        }
        curStatement = scope; 
    }
    else if(typeIndicator.find(_str) != typeIndicator.end()){
        unGetToken(keyword);
        int dataType = getDataType();
        
    }
    else{
        std::vector<Token> exp;
        getExp(exp,";");
        curStatement = new ExpStatement(parserExp(exp,1,(int)exp.size()-1));
    }
    return curStatement;
}
