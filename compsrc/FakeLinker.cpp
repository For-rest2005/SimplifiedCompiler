#include "FakeLinker.h"

std::unordered_map<std::string,Instruction*> labelPos;
std::unordered_map<Instruction*,std::string> jmpLabel;
std::unordered_map<Instruction*,Instruction*> jmpInstr;
std::vector<Instruction*> breakJmp;
std::vector<Instruction*> continueJmp;

static std::set<int> _breakJmp;
static std::set<int> _continueJmp;

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
        std::cout << cnt++ << ' ' << cur << std::endl;
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
        std::cout << id << ' ' << instr->next << ' ';
        instr->print();
        std::cout << std::endl;
        instr = instr->next;
    }
    for(auto tmp:breakJmp)
        _breakJmp.insert(tmp->id);
    for(auto tmp:continueJmp)
        _continueJmp.insert(tmp->id);
    for(auto tmp:jmpLabel){
        std::cout << tmp.first << ' ' << tmp.second << std::endl;
        if(tmp.second == ".continue")
            tmp.first->replaceJmptag(*_continueJmp.upper_bound(tmp.first->id));
        else if(tmp.second == ".break")
            tmp.first->replaceJmptag(*_breakJmp.upper_bound(tmp.first->id));
        else if(tmp.second.front() == '+' || tmp.second.front() == '-')
            tmp.first->replaceJmptag(tmp.first->id+stoi(tmp.second));
        else
            tmp.first->replaceJmptag(labelPos[tmp.second]->id);
    }
    for(auto tmp:jmpInstr)
        tmp.first->replaceJmptag(tmp.second->id);
    instr = program->front->next;
    while(instr){
        instr->print();
        instr = instr->next;
    }
}