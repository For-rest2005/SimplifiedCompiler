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
#define INSTR_GETI 60
#define INSTR_PUTC 70
#define INSTR_EXIT 100

#define RIP 0
#define RBQ 1
#define RSP 2
#define CON0 101
#define CON1 102
#define CON 100

inline void concatenate(Instruction *&preback,Instruction *front,Instruction *back){
    preback->next = front;
    preback = back;
}

inline void stackPushVar(Instruction *&back,int varAddr){
    //to be modify
    Instruction *instr2 = new Instruction(INSTR_SUB,RSP,CON1,RSP);
    Instruction *instr1 = new Instruction(INSTR_SARR,varAddr,0,RSP,instr2);
    concatenate(back,instr1,instr2);
}

inline void stackPushConstant(Instruction *&back,int value){
    //This function push a constant to the top of the stack
    Instruction *instr3 = new Instruction(INSTR_SUB,RSP,CON1,RSP);
    Instruction *instr2 = new Instruction(INSTR_SARR,CON,0,RSP,instr3);
    Instruction *instr1 = new Instruction(INSTR_LI,value,CON,0,instr2);
    concatenate(back,instr1,instr3);
}

inline void nodeConcatenate(ASTNode *pre,ASTNode *cur){
    pre->codeGenerate();
    concatenate(pre->back,cur->front->next,cur->back);
    delete cur->front;
}

void VariableExp::codeGenerate(){
    auto varinfo = varEnvir.getVar(name,globalBit);
    dataType = varinfo.first;
    leftBit = true;
    stackPushConstant(back,varinfo.second);
}

void ArrayExp::codeGenerate(){
    nodeConcatenate(index,this);
    auto varinfo = varEnvir.getVar(name,globalBit);
    leftBit = true;
    if(varinfo.first == DATATYPE_INTPOINTER) 
        dataType = DATATYPE_INT;
    else errorReport("Invalid array expression");
    Instruction *instr1 = new Instruction(INSTR_ADD,RSP,varinfo.second,RSP);
    concatenate(back,instr1,instr1);
}

void ConstantExp::codeGenerate(){
    switch (dataType)
    {
    case DATATYPE_INT:
        stackPushConstant(back,stoi(value));
        break;
    case STRINGCONSTANT:
        
        break;
    }
}

void UnaryOp::codeGenerate(){

}

void BinaryOp::codeGenerate(){

}

void TernaryOp::codeGenerate(){

}

void FunctionCall::codeGenerate(){
    
}