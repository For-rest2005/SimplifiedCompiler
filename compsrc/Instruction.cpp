#include "Instruction.h"

Instruction::Instruction(int _op,int _x,int _y,int _z):next(nullptr),op(_op),x(_x),y(_y),z(_z){}
Instruction::Instruction(int _op,int _x,int _y,int _z,Instruction *_next):op(_op),x(_x),y(_y),z(_z),next(_next){}
Instruction::Instruction(int _op,int _x,int _y,int _z,const std::string &_label)
:label(_label),next(nullptr),op(_op),x(_x),y(_y),z(_z){}
Instruction::Instruction(int _op,int _x,int _y,int _z,const std::string &_label,Instruction *_next)
:label(_label),next(_next),op(_op),x(_x),y(_y),z(_z){}
void Instruction::print(){
    std::cout << op << ' ';
    if(op == 100);
    else if(op == 50 || op == 60 || op == 30 || op == 40 || op == 70)
        std::cout << x << ' ';
    else if(op == 0 || op == 3 || op == 14 || op == 20)
        std::cout << x << ' ' << y << ' ';
    else 
        std::cout << x << ' ' << y << ' ' << z << ' ';
    if(next) next->print();
}
void Instruction::replaceLable(int _x){x = _x;}
