#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_
#include "Shared.h"

class Instruction{
    int op;
    int x,y,z;
public:
    Instruction *next;
    std::string label;
    Instruction();
    Instruction(int,int,int,int,Instruction*);
    Instruction(int,int,int,int);
    Instruction(int,int,int,int,const std::string&);
    Instruction(int,int,int,int,const std::string&,Instruction*);
    ~Instruction() = default;
    void print();
    void replaceLable(int);
};

#endif