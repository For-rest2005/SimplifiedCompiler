#include "Shared.h"
#include "Instruction.h"
#include "Statement.h"
#include "Expression.h"
#include "ASTNode.h"

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
#define RAX 3
#define T0 4
#define T1 5
#define T2 6
#define CON0 101
#define CON1 102
#define CON 100

extern std::unordered_map<std::string,Instruction*> labelPos;
extern std::unordered_map<Instruction*,std::string> jmpLabel;
extern std::unordered_map<Instruction*,Instruction*> jmpInstr;
extern std::vector<Instruction*> breakJmp;
extern std::vector<Instruction*> continueJmp;

inline void concatenate(Instruction *&preback,Instruction *front,Instruction *back){
    preback->next = front;
    preback = back;
}

inline void nodeConcatenate(ASTNode *cur,ASTNode *next){
    next->codeGenerate();
    if(next->front->next)
        concatenate(cur->back,next->front->next,next->back);
    delete next->front;
}

inline void stackPushConstant(Expression *exp,int value){
    //This function append the assembly code that push a constant to the top of the stack
    exp->pushbackInstr(INSTR_SUB,RSP,CON1,RSP);
    exp->pushbackInstr(INSTR_LI,value,CON,0);
    exp->pushbackInstr(INSTR_SARR,CON,0,RSP);
}

inline void nodeConcatenateOptional(ASTNode *cur,Expression *next){
    next->codeGenerateOptional();
    if(next->front->next) 
        concatenate(cur->back,next->front->next,next->back);
    delete next->front;
}

void VariableExp::codeGenerate(){
    auto varinfo = varEnvir.getVar(name,globalBit);
    dataType = varinfo.first;
    pushbackInstr(INSTR_SUB,RSP,CON1,RSP);
    if(globalBit){
        pushbackInstr(INSTR_SARR,varinfo.second,0,RSP);
    }
    else{
        pushbackInstr(INSTR_RARR,-varinfo.second,RBQ,T0);
        pushbackInstr(INSTR_SARR,T0,0,RSP);
    }
}

void VariableExp::codeGenerateOptional(){
    auto varinfo = varEnvir.getVar(name,globalBit);
    dataType = varinfo.first;
    if(globalBit) stackPushConstant(this,varinfo.second);
    else{
        pushbackInstr(INSTR_SUB,RSP,CON1,RSP);
        pushbackInstr(INSTR_LI,varinfo.second,CON,0);
        pushbackInstr(INSTR_SUB,RBQ,CON,T0);
        pushbackInstr(INSTR_SARR,T0,0,RSP);
    }
}

void ArrayExp::codeGenerate(){
    nodeConcatenate(this,index);
    auto varinfo = varEnvir.getVar(name,globalBit);
    if(varinfo.first == DATATYPE_INTPOINTER) 
        dataType = DATATYPE_INT;
    else errorReport("Invalid array expression");
    if(globalBit){
        pushbackInstr(INSTR_LI,varinfo.second,CON,0);
        pushbackInstr(INSTR_RARR,0,CON,CON);
        pushbackInstr(INSTR_RARR,0,RSP,T0);
        pushbackInstr(INSTR_ADD,T0,CON,T0);
        pushbackInstr(INSTR_RARR,0,T0,T0);
        pushbackInstr(INSTR_SARR,T0,0,RSP);
    }
    else{
        pushbackInstr(INSTR_RARR,-varinfo.second,RBQ,T0);
        pushbackInstr(INSTR_RARR,0,RSP,T1);
        pushbackInstr(INSTR_ADD,T0,T1,T0);
        pushbackInstr(INSTR_RARR,0,T0,T0);
        pushbackInstr(INSTR_SARR,T0,0,RSP);
    }
    delete index;
}

void ArrayExp::codeGenerateOptional(){
    nodeConcatenate(this,index);
    auto varinfo = varEnvir.getVar(name,globalBit);
    if(varinfo.first == DATATYPE_INTPOINTER) 
        dataType = DATATYPE_INT;
    else errorReport("Invalid array expression");
    pushbackInstr(INSTR_LI,varinfo.second,T1,0);
    if(!globalBit)
        pushbackInstr(INSTR_SUB,RBQ,T1,T1);
    pushbackInstr(INSTR_RARR,0,T1,T1);
    pushbackInstr(INSTR_RARR,0,RSP,T0);
    pushbackInstr(INSTR_ADD,T1,T0,T0);
    pushbackInstr(INSTR_SARR,T0,0,RSP);
    delete index;
}

void ConstantExp::codeGenerate(){
    switch (dataType)
    {
    case DATATYPE_INT:
        stackPushConstant(this,stoi(value));
        break;
    case DATATYPE_STRINGCONSTANT:
        pushbackInstr(INSTR_LI,value.size()+1,CON,0);
        pushbackInstr(INSTR_SUB,RSP,CON,RSP);
        pushbackInstr(INSTR_MOV,RSP,T0,0);
        for(int i = 0;i < value.size();i++){
            pushbackInstr(INSTR_LI,(int)value[i],CON,0);
            pushbackInstr(INSTR_SARR,CON,0,T0);
            pushbackInstr(INSTR_ADD,T0,CON1,T0);
        }
        pushbackInstr(INSTR_SARR,CON0,0,T0);
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
        nodeConcatenateOptional(this,first);
        if(first->dataType == DATATYPE_INT)
            dataType = DATATYPE_INTPOINTER;
        else errorReport("Invalid unary operator " + op);
    }
    else{
        // The pointer must store the absolute address
        nodeConcatenate(this,first);
        if(first->dataType == DATATYPE_INTPOINTER)
            dataType = DATATYPE_INT;
        else 
            errorReport("Invalid unary operator " + op);
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
        pushbackInstr(INSTR_RARR,0,RSP,T0);
        pushbackInstr(INSTR_ADD,RSP,CON1,RSP);
        //T0 stores the absolute address of left variable
        if(first->dataType == DATATYPE_INTPOINTER && second->dataType == DATATYPE_STRINGCONSTANT){
            // In this kind of operation, we store 0 at the top of the stack 
            dataType = DATATYPE_INT;
            pushbackInstr(INSTR_RARR,0,T0,T0);
            pushbackInstr(INSTR_RARR,0,RSP,T1);
            pushbackInstr(INSTR_JALI,0,0,0,"+5");
            pushbackInstr(INSTR_SARR,T1,0,T0);
            pushbackInstr(INSTR_ADD,RSP,CON1,RSP);
            pushbackInstr(INSTR_ADD,T0,CON1,T0);
            pushbackInstr(INSTR_RARR,0,RSP,T1);
            pushbackInstr(INSTR_JALE,T1,0,0,"-4");
        }
        else if(first->dataType == second->dataType){
            dataType = first->dataType;
            pushbackInstr(INSTR_RARR,0,RSP,T1);
            pushbackInstr(INSTR_SARR,T1,0,T0);
            pushbackInstr(INSTR_SARR,T1,0,RSP);
        }
        else
            errorReport("Invalid operator " + op);
    }
    else if(op == "!=" || op == "<=" || op == ">="){
        nodeConcatenate(this,first);
        nodeConcatenate(this,second);
        if(first->dataType == DATATYPE_INT && first->dataType == DATATYPE_INT)
            dataType = DATATYPE_INT;
        else
            errorReport("Invalid operator " + op);
        pushbackInstr(INSTR_RARR,0,RSP,T1);
        pushbackInstr(INSTR_ADD,RSP,CON1,RSP);
        pushbackInstr(INSTR_RARR,0,RSP,T0);
        pushbackInstr((op == "!="?INSTR_BEQ:op == "<="?INSTR_GT:INSTR_LT),T0,T1,T0);
        pushbackInstr(INSTR_NOT,T0,T0,0);
        pushbackInstr(INSTR_SARR,T0,0,RSP);
    }
    else if(op == ","){
        nodeConcatenate(this,second);
        nodeConcatenate(this,first);
        dataType = first->dataType;
        pushbackInstr(INSTR_ADD,RSP,CON1,RSP);
    }
    else{
        nodeConcatenate(this,first);
        nodeConcatenate(this,second);
        bool che1 = (first->dataType == DATATYPE_INT && second->dataType == DATATYPE_INTPOINTER);
        bool che2 = (first->dataType == DATATYPE_INTPOINTER && second->dataType == DATATYPE_INT);
        if(first->dataType == DATATYPE_INT && second->dataType == DATATYPE_INT)
            dataType = DATATYPE_INT;
        else if((op == "+" && (che1 || che2)) || (op == "-" && che2))
            dataType = DATATYPE_INTPOINTER; 
        else
            errorReport("Invalid operator " + op);
        pushbackInstr(INSTR_RARR,0,RSP,T1);
        pushbackInstr(INSTR_ADD,RSP,CON1,RSP);
        pushbackInstr(INSTR_RARR,0,RSP,T0);
        pushbackInstr(opCoInstr.at(op),T0,T1,T0);
        pushbackInstr(INSTR_SARR,T0,0,RSP);
    }
    delete first;
    delete second;
}

void TernaryOp::codeGenerate(){
    nodeConcatenate(this,first);
    nodeConcatenate(this,second);
    nodeConcatenate(this,third);
    if(op == "?:" ){
        if(second->dataType != third->dataType)
            errorReport("Invalid operator "+op);
        dataType = second->dataType;
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
    delete first;
    delete second;
    delete third;
}

void FunctionCall::codeGenerate(){
    static constexpr int bias = 5;
    pushbackInstr(INSTR_SUB,RSP,CON1,RSP);
    pushbackInstr(INSTR_SARR,RBQ,0,RSP);
    pushbackInstr(INSTR_SUB,RSP,CON1,RSP);
    FunctionData _fun = funEnvir.getFun(name);
    dataType = _fun.returnType;
    if(arguments.size() != _fun.arguments.size())
        errorReport("Invalid function call(arguments size mismatch)");
    for(int i = 0;i < arguments.size();i++){
        nodeConcatenate(this,arguments[i]);
        if(arguments[i]->dataType != _fun.arguments[i].first)
            errorReport("Invalid function call(arguments type mismatch)");
    }
    pushbackInstr(INSTR_LI,arguments.size(),CON,0);
    pushbackInstr(INSTR_ADD,CON,RSP,RBQ);
    pushbackInstr(INSTR_MOV,RIP,T1,0);
    pushbackInstr(INSTR_LI,bias,CON,0);
    pushbackInstr(INSTR_ADD,CON,T1,T1);
    pushbackInstr(INSTR_SARR,T1,0,RBQ);
    pushbackInstr(INSTR_JALI,0,0,0,name);
    pushbackInstr(INSTR_ADD,RBQ,CON1,RSP);
    pushbackInstr(INSTR_RARR,0,RSP,RBQ);
    pushbackInstr(INSTR_SARR,RAX,0,RSP);    
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
    delete value;
}

void ReadStatement::codeGenerate(){
    nodeConcatenate(this,addr);
    pushbackInstr(INSTR_READ,T0,0,0);
    pushbackInstr(INSTR_RARR,0,RSP,T1);
    pushbackInstr(INSTR_SARR,T0,0,T1);
    pushbackInstr(INSTR_ADD,RSP,CON1,RSP);
    delete addr;
}

void PutcharStatement::codeGenerate(){
    nodeConcatenate(this,value);
    pushbackInstr(INSTR_RARR,0,RSP,T0);
    pushbackInstr(INSTR_PUTC,T0,0,0);
    pushbackInstr(INSTR_ADD,RSP,CON1,RSP);
    delete value;
}

void ReturnStatement::codeGenerate(){
    if(value)   
        nodeConcatenate(this,value);
    pushbackInstr(INSTR_RARR,0,RSP,RAX);
    pushbackInstr(INSTR_RARR,0,RBQ,T0);
    pushbackInstr(INSTR_JAL,T0,0,0);
    delete value;
}

void WhileStatement::codeGenerate(){
    pushbackInstr(INSTR_JALI,0,0,0);
    Instruction* f1 = back;
    nodeConcatenate(this,body);
    Instruction* bodyInstr = f1->next;
    Instruction* f2 = back;
    nodeConcatenate(this,condition);
    Instruction* conditionInstr = f2->next;
    pushbackInstr(INSTR_RARR,0,RSP,T0);
    pushbackInstr(INSTR_ADD,RSP,CON1,RSP);
    pushbackInstr(INSTR_JALE,T0,0,0);
    Instruction* f3 = back;
    pushbackInstr(INSTR_LI,0,CON,0);//Occupy
    jmpInstr[f1] = conditionInstr;
    jmpInstr[f3] = bodyInstr;
    breakJmp.push_back(back);
    continueJmp.push_back(conditionInstr);
    delete condition;
    delete body;
}

void IfStatement::codeGenerate(){
    nodeConcatenate(this,condition);
    pushbackInstr(INSTR_RARR,0,RSP,T0);
    pushbackInstr(INSTR_ADD,RSP,CON1,RSP);
    pushbackInstr(INSTR_JALE,T0,0,0);
    Instruction* f1 = back;
    if(body2) nodeConcatenate(this,body2);
    pushbackInstr(INSTR_JALI,0,0,0);
    Instruction* f2 = back;
    nodeConcatenate(this,body1);
    pushbackInstr(INSTR_LI,0,CON,0);
    jmpInstr[f1] = f2->next;
    jmpInstr[f2] = back;
    delete body1;
    delete body2;
    delete condition;
}

void GlobalVarDeclaration::codeGenerate(){
    varEnvir.addVar(varName,dataType,1);
}

void GlobalArrayDeclaration::codeGenerate(){
    int addr,p;
    if(dataType == DATATYPE_INT)
        addr = varEnvir.addVar("."+varName,DATATYPE_INT,size);
    p = varEnvir.addVar(varName,DATATYPE_INTPOINTER,1);
    pushbackInstr(INSTR_LI,addr,CON,0);
    pushbackInstr(INSTR_LI,p,T0,0);
    pushbackInstr(INSTR_SARR,CON,0,T0);
    //absolute address
}

void LocalVarDeclaration::codeGenerate(){
    varEnvir.addVar(varName,dataType,1);
    pushbackInstr(INSTR_SUB,RSP,CON1,RSP);
}

void LocalArrayDeclaration::codeGenerate(){
    int addr,p;
    if(dataType == DATATYPE_INT)
        addr = varEnvir.addVar("."+varName,DATATYPE_INT,size);
    p = varEnvir.addVar(varName,DATATYPE_INTPOINTER,1);
    pushbackInstr(INSTR_LI,size+1,CON,0);
    pushbackInstr(INSTR_SUB,RSP,CON,RSP);
    pushbackInstr(INSTR_LI,addr,CON,0);
    pushbackInstr(INSTR_SUB,RBQ,CON,T0);
    pushbackInstr(INSTR_SARR,T0,0,RSP);
    //Here what we get is a pointer pointing to the head of a block of memory in size of $size
}

void FunctionDeclaration::codeGenerate(){
    FunctionData funData(returnDataType,arguments);
    funEnvir.addFun(funName,funData);
}

void FunctionDefinition::codeGenerate(){
    FunctionData funData(returnDataType,arguments);
    funEnvir.addFun(funName,funData);
    varEnvir.enterScope();
    for(auto tmp:arguments){
        varEnvir.addVar(tmp.second,tmp.first,1);
    }
    nodeConcatenate(this,body);
    if(labelPos.find(funName) != labelPos.end())
        errorReport("Redefine function "+funName);
    labelPos[funName] = this->front->next;
    varEnvir.exitScope();
    delete body;
}

void Scope::codeGenerate(){
    varEnvir.enterScope();
    for(auto tmp:body){
        nodeConcatenate(this,tmp);
        delete tmp;
    }
    varEnvir.exitScope();
}

void BreakStatement::codeGenerate(){
    pushbackInstr(INSTR_JALI,0,0,0,".break");
}

void ContinueStatement::codeGenerate(){
    pushbackInstr(INSTR_JALI,0,0,0,".continue");
}

void Program::codeGenerate(){
    static constexpr int stacktop = 50000;
    pushbackInstr(INSTR_LI,stacktop,RSP,0);
    pushbackInstr(INSTR_LI,stacktop,RBQ,0);
    pushbackInstr(INSTR_LI,0,CON0,0);
    pushbackInstr(INSTR_LI,1,CON1,0);
    pushbackInstr(INSTR_LI,6,stacktop,0);
    pushbackInstr(INSTR_JALI,0,0,0,"main");
    pushbackInstr(INSTR_EXIT,0,0,0);
}