#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_
#include "Shared.h"

class Instruction{
    int op;
    int x,y,z;
public:
    int id;
    Instruction *next;
    Instruction();
    Instruction(int,int,int,int,Instruction*);
    Instruction(int,int,int,int);
    ~Instruction() = default;
    void print();
    void replaceJmptag(int);
};

#endif