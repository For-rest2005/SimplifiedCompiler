#ifndef _ASTNODE_H_
#define _ASTNODE_H_

#include<string>
#include"Shared.h"
class ASTNode{
public:
    std::string ascode;//Maybe we need a data structure to store the assembly codes 
    virtual ~ASTNode() = 0;
    ASTNode() = default;
    // virtual void codeGenerate(VarTable&,FunctionTable&);
};

#endif 