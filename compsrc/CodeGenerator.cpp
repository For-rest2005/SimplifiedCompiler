#include "Shared.h"

#define INSTR_LI 0
#define INSTR_SARR 1
#define INSTR_RARR 2
#define INSTR_MOV 3
#define INSTR_ADD 4
#define INSTR_SUB 5
#define INSTR_MUL 6
#define INSTR_DIV 7
#define INSTR_REM 8
#define INSTR_BEQ 9
#define INSTR_GT 10
#define INSTR_LT 11
#define INSTR_ANDB 12
#define INSTR_ORB 13
#define INSTR_NOT 14
#define INSTR_AND 15
#define INSTR_OR 16
#define INSTR_XOR 17
#define INSTR_SLL 18
#define INSTR_SRA 19
#define INSTR_JALE 20
#define INSTR_JALI 30
#define INSTR_JAL 40
#define INSTR_PUTI 50
#define INSTR_READ 60
#define INSTR_PUTC 70
#define INSTR_EXIT 100
const static std::unordered_map<std::string,int> opCoInstr = {
    {"+",INSTR_ADD},{"-",INSTR_SUB},{"*",INSTR_MUL},{"/",INSTR_DIV},{"%",INSTR_REM},{"==",INSTR_BEQ},{">",INSTR_GT},
    {"<",INSTR_LT},{"&&",INSTR_ANDB},{"||",INSTR_ORB},{"&",INSTR_OR},{"|",INSTR_XOR},{"^",INSTR_XOR},{"<<",INSTR_SLL},
    {">>",INSTR_SRA}
};

//Fake registers and specific memory address
#define RIP 0
#define RBQ 1
#define RSP 2 //RSP points to the last data in the stack
#define T0 3
#define T1 4
#define T2 5
#define CON0 101
#define CON1 102
#define CON 100

inline void concatenate(Instruction *&preback,Instruction *front,Instruction *back){
    preback->next = front;
    preback = back;
}

inline void stackPushConstant(Expression *exp,int value){
    //This function append the assembly code that push a constant to the top of the stack
    exp->pushbackInstr(INSTR_SUB,RSP,CON1,RSP);
    exp->pushbackInstr(INSTR_LI,value,CON,0);
    exp->pushbackInstr(INSTR_SARR,CON,0,RSP);
}

inline void nodeConcatenate(ASTNode *cur,ASTNode *next){
    next->codeGenerate();
    concatenate(cur->back,next->front->next,next->back);
    delete next->front;
}

inline void nodeConcatenateOptional(ASTNode *cur,Expression *next){
    next->codeGenerateOptional();
    concatenate(cur->back,next->front->next,next->back);
    delete next->front;
}

void VariableExp::codeGenerate(){
    auto varinfo = varEnvir.getVar(name,globalBit);
    dataType = varinfo.first;
    if(globalBit){
        pushbackInstr(INSTR_SUB,RSP,CON1,RSP);
        pushbackInstr(INSTR_SARR,varinfo.second,0,RSP);
    }
    else{
        pushbackInstr(INSTR_SUB,RSP,CON1,RSP);
        pushbackInstr(INSTR_RARR,RBQ,-varinfo.second,T0);
        pushbackInstr(INSTR_SARR,T0,0,RSP);
    }
}

void VariableExp::codeGenerateOptional(){
    auto varinfo = varEnvir.getVar(name,globalBit);
    dataType = varinfo.first;
    stackPushConstant(this,varinfo.second);
}

void ArrayExp::codeGenerate(){
    nodeConcatenate(this,index);
    auto varinfo = varEnvir.getVar(name,globalBit);
    if(varinfo.first == DATATYPE_INTPOINTER) 
        dataType = DATATYPE_INT;
    else errorReport("Invalid array expression");
    if(globalBit){
        pushbackInstr(INSTR_LI,varinfo.second,CON,0);
        pushbackInstr(INSTR_RARR,0,RSP,T0);   
        pushbackInstr(INSTR_ADD,T0,CON,T0);
        pushbackInstr(INSTR_SARR,T0,0,RSP);
    }
    else{
        pushbackInstr(INSTR_RARR,RBQ,-varinfo.second,T0);
        pushbackInstr(INSTR_RARR,0,RSP,T1);
        pushbackInstr(INSTR_ADD,T0,T1,T0);
        pushbackInstr(INSTR_RARR,0,T0,T0);
        pushbackInstr(INSTR_SARR,T0,0,RSP);
    }
}

void ArrayExp::codeGenerateOptional(){
    nodeConcatenate(this,index);
    auto varinfo = varEnvir.getVar(name,globalBit);
    if(varinfo.first == DATATYPE_INTPOINTER) 
        dataType = DATATYPE_INT;
    else errorReport("Invalid array expression");
    pushbackInstr(INSTR_LI,varinfo.second,CON,0);
    pushbackInstr(INSTR_RARR,0,RSP,T0);
    pushbackInstr(INSTR_ADD,CON,T0,T0);
    pushbackInstr(INSTR_SARR,T0,0,RSP);
}

void ConstantExp::codeGenerate(){
    switch (dataType)
    {
    case DATATYPE_INT:
        stackPushConstant(this,stoi(value));
        break;
    case STRINGCONSTANT:
        stackPushConstant(this,0);
        for(int i = (int)value.size()-1;i > 0;i--)
            stackPushConstant(this,value[i]);
        break;
    }
}

void UnaryOp::codeGenerate(){
    if(op == "+" || op == "-"){
        nodeConcatenate(this,first);
        if(first->dataType == DATATYPE_INT)
            dataType = DATATYPE_INT;
        else 
            errorReport("Invalid unory operator " + op);
        pushbackInstr(INSTR_RARR,0,RSP,T0);
        pushbackInstr(opCoInstr.at(op),CON0,T0,T0);
        pushbackInstr(INSTR_SARR,T0,0,RSP);
    }
    else if(op == "&"){
        first->codeGenerateOptional();
        if(first->dataType == DATATYPE_INT)
            dataType == DATATYPE_INTPOINTER;
        else errorReport("Invalid unary operator " + op);
        concatenate(back,first->front,first->back);
        delete first->front;
    }
    else{
        if(first->dataType = DATATYPE_INTPOINTER)
            dataType = DATATYPE_INT;
        else 
            errorReport("Invalid unary operator " + op);
        nodeConcatenate(this,first);
        pushbackInstr(INSTR_RARR,0,RSP,T0);
        pushbackInstr(INSTR_RARR,0,T0,T0);
        pushbackInstr(INSTR_SARR,T0,0,RSP);
    }
    delete first;
}

void BinaryOp::codeGenerate(){
    if(op == "="){
        nodeConcatenate(this,second);
        nodeConcatenateOptional(this,first);
        if(!first->globalBit){
            pushbackInstr(INSTR_RARR,0,RSP,T0);
            pushbackInstr(INSTR_SUB,CON0,T0,T0);
            pushbackInstr(INSTR_RARR,RBQ,T0,T0);
        }
        pushbackInstr(INSTR_ADD,RSP,CON1,RSP);
        if(first->dataType == DATATYPE_INTPOINTER && second->dataType == DATATYPE_STRINGCONSTANT){
            // In this kind of operation, we store 0 at the top of the stack 
            dataType = DATATYPE_INT;
            pushbackInstr(INSTR_RARR,0,RSP,T1);
            pushbackInstr(INSTR_JALI,0,0,0,"");
            pushbackInstr(INSTR_SARR,T1,0,T0);
            pushbackInstr(INSTR_ADD,RSP,CON1,RSP);
            pushbackInstr(INSTR_ADD,T0,CON1,T0);
            pushbackInstr(INSTR_RARR,0,RSP,T1);
            pushbackInstr(INSTR_JALE,T1,0,0,"-4");
        }
        else if(first->dataType == second ->dataType){
            dataType = first->dataType;
            pushbackInstr(INSTR_SARR,0,RSP,T1);
            pushbackInstr(INSTR_SARR,T1,0,T0);
            pushbackInstr(INSTR_SARR,T1,0,RSP);
        }
        else
            errorReport("Invalid operator " + op);
    }
    else if(op == "!=" || op == "<=" || op == ">="){
        nodeConcatenate(this,first);
        nodeConcatenate(this,second);
        pushbackInstr(INSTR_RARR,0,RSP,T1);
        pushbackInstr(INSTR_ADD,RSP,CON1,RSP);
        pushbackInstr(INSTR_RARR,0,RSP,T0);
        pushbackInstr((op == "!="?INSTR_BEQ:op == "<="?INSTR_GT:INSTR_LT),T0,T1,T0);
        pushbackInstr(INSTR_NOT,T0,T0,0);
        pushbackInstr(INSTR_SARR,T0,0,RSP);
    }
    else{
        nodeConcatenate(this,first);
        nodeConcatenate(this,second);
        pushbackInstr(INSTR_RARR,0,RSP,T1);
        pushbackInstr(INSTR_ADD,RSP,CON1,RSP);
        pushbackInstr(INSTR_RARR,0,RSP,T0);
        pushbackInstr(opCoInstr.at(op),T0,T1,T0);
        pushbackInstr(INSTR_SARR,T0,0,RSP);
    }
    delete first,second;
}

void TernaryOp::codeGenerate(){
    nodeConcatenate(this,first);
    nodeConcatenate(this,second);
    nodeConcatenate(this,third);
    if(op == "?:" ){
        if(second->dataType != third->dataType)
            errorReport("Invalid operator "+op);
        pushbackInstr(INSTR_RARR,0,RSP,T2);
        pushbackInstr(INSTR_ADD,RSP,CON1,RSP);
        pushbackInstr(INSTR_RARR,0,RSP,T1);
        pushbackInstr(INSTR_ADD,RSP,CON1,RSP);
        pushbackInstr(INSTR_RARR,0,RSP,T0);
        pushbackInstr(INSTR_JALE,T0,0,0,"+3");
        pushbackInstr(INSTR_SARR,T2,0,RSP);
        pushbackInstr(INSTR_JALI,0,0,0,"+2");
        pushbackInstr(INSTR_SARR,T1,0,RSP);
    }
    delete first,second,third;
}

void FunctionCall::codeGenerate(){

    for(Expression *exp:arguments)
        delete exp;
}

void ExpStatement::codeGenerate(){
    nodeConcatenate(this,body);
    pushbackInstr(INSTR_ADD,RSP,CON1,RSP);
    delete body;
}

void PrintStatement::codeGenerate(){
    nodeConcatenate(this,value);
    pushbackInstr(INSTR_RARR,0,RSP,T0);
    pushbackInstr(INSTR_PUTI,T0,0,0);
    pushbackInstr(INSTR_ADD,RSP,CON1,RSP);
}

void ReadStatement::codeGenerate(){
    nodeConcatenate(this,addr);
    pushbackInstr(INSTR_READ,T0,0,0);
    pushbackInstr(INSTR_RARR,0,RSP,T1);
    pushbackInstr(INSTR_SARR,T0,0,T1);
    pushbackInstr(INSTR_ADD,RSP,CON1,RSP);
}

void PutcharStatement::codeGenerate(){
    nodeConcatenate(this,value);
    pushbackInstr(INSTR_RARR,0,RSP,T0);
    pushbackInstr(INSTR_PUTC,T0,0,0);
    pushbackInstr(INSTR_ADD,RSP,CON1,RSP);
}