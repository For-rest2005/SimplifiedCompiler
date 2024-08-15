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

Statement* getStatementLocal(){
    Token keyword = getToken();
    std::string _str = keyword.value();
    Statement *curStatement;
    Expression *exp;
    Token bufferToken;
    if(_str == "while"){
        skipTokens();
        exp = parseExp1();
        skipTokens();
        curStatement = new WhileLoop(exp,getStatementLocal());
    }
    else if(_str == "if"){
        skipTokens();
        exp = parseExp1();
        skipTokens();
        curStatement = getStatementLocal();
        bufferToken = getToken();
        if(bufferToken.value() == "else")
            curStatement = new IfCondition(exp,curStatement,getStatementLocal());
        else{
            unGetToken(bufferToken);
            curStatement = new IfCondition(exp,curStatement,nullptr);
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
        Token name = getToken();
        Token op = getToken();
        if(op.value() == ";"){
            curStatement = new LocalVarDeclaration(dataType,name.value());
        }
        else if(op.value() == "["){
            int _size = getToken().toInteger();
            skipTokens(2);
            curStatement = new LocalArrayDeclaration(dataType,name.value(),_size);
        }
    }
    else{
        exp = parseExp1();
        skipTokens();
        curStatement = new ExpStatement(exp);
    }
    return curStatement;
}

binaryParse::binaryParse(const std::vector<std::string> &_op,std::function<Expression*()> _next):op(_op),next(_next){}
bool binaryParse::checkOp(std::string _str){
    for(auto obj:op)
        if(_str == obj) return 1;
    return 0;
}
Expression* binaryParse::operator()(){
    Expression *first,*second;
    first = next();
    Token buffer = getToken();
    if(checkOp(buffer.value())){
        second = operator()();
        return new BinaryOp(first,second,buffer.value());
    }
    return first;
}
const std::function<Expression*()> parseExp1 = binaryParse({","},parseExp2());
const std::function<Expression*()> parseExp2();
Expression* parseExp3();
Expression* parseExp4();
Expression* parseExp5();
Expression* parseExp6();
Expression* parseExp7();
Expression* parseExp8();
Expression* parseExp9();
Expression* parseExp10();
Expression* parseExp11();
Expression* parseExp12();
Expression* parseExp13();
Expression* parseExp14();
Expression* parseExp15();
Expression* parseExp16();
Expression *parseExp(){
    return parseExp1();
}
