#ifndef _ASTNODE_H_
#define _ASTNODE_H_

#include<string>
#include"Shared.h"
class ASTNode{
protected:
    static StackAllocator stackAlloc;
    static StaticAllocator staticAlloc;
    static VarTable varEnvir;
    static FunctionTable funEnvir;
public:
    Instruction *front,*back;//The two pointers point to an empty instruction object
    virtual ~ASTNode() = default;
    ASTNode();
    virtual void codeGenerate() = 0;
};

#endif 