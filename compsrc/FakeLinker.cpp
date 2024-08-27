#include "FakeLinker.h"

std::unordered_map<std::string,Instruction*> labelPos;
std::unordered_map<Instruction*,std::string> jmpLabel;
std::unordered_map<Instruction*,Instruction*> jmpInstr;
std::vector<Instruction*> breakJmp;
std::vector<Instruction*> continueJmp;

static std::vector<int> _breakJmp;
static std::vector<int> _continueJmp;

int cnt = 0;

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
    std::cout << "enter linker" << std::endl;
    Program *program = new Program();
    program->next = getStatementGlobal();
    std::cout << "Parser successfully" << std::endl;
    program->codeGenerate();
    GlobalStatement *cur = program->next;
    while(cur){
        nodeConcatenate(program,cur);
        cur = cur->next;
    }
    std::cout << "Code generation is done" << std::endl;
    Instruction *instr = program->front->next;
    int id = 0;
    delete program->front;
    while(instr){
        instr->id = id;
        id++;
        instr = instr->next;
    }
    for(auto tmp:breakJmp)
        _breakJmp.push_back(tmp->id);
    for(auto tmp:continueJmp)
        _continueJmp.push_back(tmp->id);
    sort(_breakJmp.begin(),_breakJmp.end());
    sort(_continueJmp.begin(),_continueJmp.end());
    for(auto tmp:jmpLabel){
        if(tmp.second == ".continue")
            tmp.first->replaceJmptag(*upper_bound(_continueJmp.begin(),_continueJmp.end(),tmp.first->id));
        else if(tmp.second == ".break")
            tmp.first->replaceJmptag(*upper_bound(_breakJmp.begin(),_breakJmp.end(),tmp.first->id));
        else if(tmp.second.front() == '+' || tmp.second.front() == '-')
            tmp.first->replaceJmptag(tmp.first->id+stoi(tmp.second));
        else
            tmp.first->replaceJmptag(labelPos[tmp.second]->id);
    }
    for(auto tmp:jmpInstr)
        tmp.first->replaceJmptag(tmp.second->id);
    std::cout << id << std::endl;
    instr = program->front->next;
    while(instr){
        instr->print();
        instr = instr->next;
    }
}