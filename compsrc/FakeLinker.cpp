#include "FakeLinker.h"
#include "Parser.h"
std::unordered_map<std::string,Instruction*> labelPos;
std::unordered_map<Instruction*,std::string> jmpLabel;
std::unordered_map<Instruction*,Instruction*> jmpInstr;
std::vector<Instruction*> breakJmp;
std::vector<Instruction*> continueJmp;

inline void concatenate(Instruction *&preback,Instruction *front,Instruction *back){
    preback->next = front;
    preback = back;
}

inline void nodeConcatenate(ASTNode *cur,ASTNode *next){
    next->codeGenerate();
    if(next->front->next) concatenate(cur->back,next->front->next,next->back);
    delete next->front;
}

void linker(){
    Program* program;
    program->next = getStatementGlobal();
    program->codeGenerate();
    Statement* cur = program->next;
    while(cur){
        nodeConcatenate(program,cur);
    }

}