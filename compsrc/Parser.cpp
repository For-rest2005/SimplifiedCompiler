#include "Parser.h"

const static std::unordered_set<std::string> typeIndicator = {"int","void","int*"};
const static std::unordered_map<std::string,int> reDataType = {{"int",DATATYPE_INT},{"void",DATATYPE_VOID},{"int*",DATATYPE_INTPOINTER}};

int getDataType(){
    Token keyword = getToken();
    Token optional = getToken();
    if(keyword.type() == ENDPOINT) return -1;
    std::string _str = keyword.value()+optional.value();
    if(typeIndicator.find(_str) != typeIndicator.end())
        return reDataType.at(_str);
    unGetToken(optional);
    if(typeIndicator.find(keyword.value()) != typeIndicator.end())
        return reDataType.at(keyword.value());
    unGetToken(keyword);
    return -2;
}

GlobalStatement* getStatementGlobal(){
    int dataType = getDataType();
    if(dataType == -1) return nullptr;
    if(dataType == -2) errorReport("Invalid type indicator");
    GlobalStatement* curStatement;
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
            Token buffer = getToken();
            if(buffer.value() == ")")
                break;
            argVarType = getDataType();
            Token varName;
            varName = getToken();
            typeNameList.push_back({argVarType,varName.value()});
        }
        op = getToken();
        if(op.value() == "{"){
            unGetToken(op);
            Statement *body = getStatementLocal();
            curStatement = new FunctionDefinition(dataType,name.value(),typeNameList,body,getStatementGlobal());
        }else if(op.value() == ";"){
            curStatement = new FunctionDeclaration(dataType,name.value(),typeNameList,getStatementGlobal());
        }else{
            errorReport("Error function definition");
        }
    }
    else errorReport("Error function declaration or definition");
    return curStatement;
}

Statement* getStatementLocal(){
    Token keyword = getToken();
    std::string _str = keyword.value();
    Statement *curStatement;
    Expression *exp;
    Token buffer;
    if(_str == "while"){
        skipTokens();
        exp = parseExp();
        skipTokens();
        curStatement = new WhileStatement(exp,getStatementLocal());
    }
    else if(_str == "if"){
        skipTokens();
        exp = parseExp();
        skipTokens();
        curStatement = getStatementLocal();
        buffer = getToken();
        if(buffer.value() == "else")
            curStatement = new IfStatement(exp,curStatement,getStatementLocal());
        else{
            unGetToken(buffer);
            curStatement = new IfStatement(exp,curStatement,nullptr);
        }
    }
    else if(_str == "{"){
        Scope *scope;
        scope = new Scope();
        while((buffer = getToken()).value() != "}"){
            unGetToken(buffer);
            scope->push(getStatementLocal());
        }
        curStatement = scope; 
    }
    else if(_str == "return"){
        buffer = getToken();
        if(buffer.value() == ";")
            return new ReturnStatement(nullptr);
        unGetToken(buffer);
        Expression *value = parseExp();
        skipTokens();
        curStatement = new ReturnStatement(value);
    }
    else if(_str == "continue"){
        skipTokens();
        return new ContinueStatement();
    }
    else if(_str == "break"){
        skipTokens();
        return new BreakStatement();
    }
    else if(_str == "read"){
        Expression *addr = parseExp();
        skipTokens();
        curStatement = new ReadStatement(addr);
    }
    else if(_str == "print"){   
        Expression *value = parseExp();
        skipTokens();
        curStatement = new PrintStatement(value);
    }
    else if(_str == "putchar"){
        Expression *value = parseExp();
        skipTokens();
        curStatement = new PutcharStatement(value);
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
        unGetToken(keyword);
        exp = parseExp();
        skipTokens();
        curStatement = new ExpStatement(exp);
    }
    return curStatement;
}

Expression *parseExp();
Expression *_parseExp1();
Expression *_parseExp2();

binaryParse::binaryParse(const std::vector<std::string> &_op,std::function<Expression*()> _next):op(_op),next(_next){}
bool binaryParse::checkOp(std::string _str){
    for(auto obj:op)
        if(_str == obj) return 1;
    return 0;
}
Expression *binaryParse::operator()(){
    Expression *first;
    first = next();
    Token buffer = getToken();
    if(checkOp(buffer.value())){
        Expression *second = operator()();
        return new BinaryOp(first,second,buffer.value());
    }
    unGetToken(buffer);
    return first;
}

Expression *_parseExp16(){
    Token name = getToken();
    Token buffer = getToken();
    if(buffer.value() == "["){
        Expression *index = _parseExp1();
        skipTokens();
        return new ArrayExp(name.value(),index);
    }
    else if(buffer.value() == "("){
        std::vector<Expression*> arguments; 
        while(true){
            buffer = getToken();
            if(buffer.value() == ")")
                return new FunctionCall(name.value(),arguments);
            arguments.push_back(_parseExp2());
        }
    }
    else{
        unGetToken(buffer);
        if(name.type() == IDENTIFIER) return new VariableExp(name.value());
        else if(name.type() == INTCONSTANT) return new ConstantExp(name.value(),DATATYPE_INT);
        else if(name.type() == STRINGCONSTANT) return new ConstantExp(name.value(),DATATYPE_STRINGCONSTANT);
        else return nullptr;
    }
}

const std::function<Expression*()> parseExp16 = _parseExp16;
Expression *_parseExp15(){
    Token buffer = getToken();
    if(buffer.value() == "("){
        Expression *exp = _parseExp1();
        skipTokens();
        return exp;
    }
    unGetToken(buffer);
    return parseExp16();
}

const std::function<Expression*()> parseExp15 = _parseExp15;
Expression *_parseExp14(){
    Token buffer = getToken();
    if(buffer.value() == "+" || buffer.value() == "-" || buffer.value() == "*" || buffer.value() == "&")
        return new UnaryOp(_parseExp14(),buffer.value());
    unGetToken(buffer);
    return parseExp15();
}

const std::function<Expression*()> parseExp14 = _parseExp14;
const std::function<Expression*()> parseExp13 = binaryParse({"*","/","%"},parseExp14);
const std::function<Expression*()> parseExp12 = binaryParse({"+","-"},parseExp13);
const std::function<Expression*()> parseExp11 = binaryParse({">>","<<"},parseExp12);
const std::function<Expression*()> parseExp10 = binaryParse({"<",">","<=",">="},parseExp11);
const std::function<Expression*()> parseExp9 = binaryParse({"==","!="},parseExp10);
const std::function<Expression*()> parseExp8 = binaryParse({"&"},parseExp9);
const std::function<Expression*()> parseExp7 = binaryParse({"^"},parseExp8);
const std::function<Expression*()> parseExp6 = binaryParse({"|"},parseExp7);
const std::function<Expression*()> parseExp5 = binaryParse({"&&"},parseExp6);
const std::function<Expression*()> parseExp4 = binaryParse({"||"},parseExp5);
Expression *_parseExp3(){
    Expression *first = parseExp4();
    Token buffer1 = getToken();
    if(buffer1.value() == "?"){
        Expression *second = _parseExp3();
        Token buffer2 = getToken();
        if(buffer2.value() != ":") errorReport(":?operator error");
        Expression *third = parseExp4();
        return new TernaryOp(first,second,third,"?:");
    }
    unGetToken(buffer1);
    return first;
}

const std::function<Expression*()> parseExp3 = _parseExp3;
const std::function<Expression*()> parseExp2 = binaryParse({"="},parseExp3);
const std::function<Expression*()> parseExp1 = binaryParse({","},parseExp2);

Expression *parseExp(){return parseExp1();}
Expression *_parseExp1(){return parseExp1();}
Expression *_parseExp2(){return parseExp2();}
