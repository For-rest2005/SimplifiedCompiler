#include "FakeLinker.h"

std::unordered_map<std::string,Instruction*> labelPos;
std::unordered_map<Instruction*,std::string> jmpLabel;
std::unordered_map<Instruction*,Instruction*> jmpInstr;
std::vector<Instruction*> breakJmp;
std::vector<Instruction*> continueJmp;

static std::vector<int> _breakJmp;
static std::vector<int> _continueJmp;


inline void concatenate(Instruction *&preback,Instruction *front,Instruction *back){
    preback->next = front;
    preback = back;
}

inline void nodeConcatenate(GlobalStatement *program,GlobalStatement *textSeg,GlobalStatement *next){
    next->codeGenerate();
    GlobalStatement *cur;
    if(next->deBit) cur = program;
    else cur = textSeg;
    if(next->front->next) concatenate(cur->back,next->front->next,next->back);
    delete next->front;
}

void linker(){
    Program *program = new Program(),*textSeg = new Program();
    program->next = getStatementGlobal();
    std::cerr << "Parser successfully" << std::endl;

    GlobalStatement *cur = program->next;
    while(cur){
        nodeConcatenate(program,textSeg,cur);
        cur = cur->next;
    }
    program->codeGenerate();
    concatenate(program->back,textSeg->front->next,textSeg->back);
    delete textSeg->front;
    std::cerr << "Code generation is done" << std::endl;

    Instruction *instr = program->front->next;
    int id = 0;
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
    std::cerr << "Linking over" << std::endl;
    
    std::cout << id << std::endl;
    instr = program->front->next;
    Instruction *pre;
    while(instr){
        instr->print();
        pre = instr;
        instr = instr->next;
        delete pre;
    }
    delete program;
}