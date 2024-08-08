#ifndef _ASTNODE_H_
#define _ASTNODE_H_

#include<string>
class ASTNode{
public:
    std::string _assemblyCode;
    virtual ~ASTNode() = 0;
    ASTNode() = default;
    virtual void codeGenerate();
};

#endif 