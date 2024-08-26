#ifndef _ASTNODE_H_
#define _ASTNODE_H_

#include<string>
#include"Shared.h"

extern std::unordered_map<std::string,Instruction*> labelPos;
extern std::unordered_map<Instruction*,std::string> jmpLabel;
extern std::unordered_map<Instruction*,Instruction*> jmpInstr;

class ASTNode{
protected:
    static VarTable varEnvir;
    static FunctionTable funEnvir;
public:
    inline void pushbackInstr(int op,int x,int y,int z){
        back->next = new Instruction(op,x,y,z);
        back = back->next;
    }
    inline void pushbackInstr(int op,int x,int y,int z,std::string label,bool type = true){
        if(type){
            back->next = new Instruction(op,x,y,z);
            back = back->next;
            jmpLabel[back] = label;
        }else{
            back->next = new Instruction(op,x,y,z);
            back = back->next;
            labelPos[label] = back;
        }
    }
    Instruction *front,*back;//The two pointers point to an empty instruction object
    virtual ~ASTNode() = default;
    ASTNode();
    virtual void codeGenerate() = 0;
};

#endif 