#ifndef _ASTNODE_H_
#define _ASTNODE_H_

#include<string>
class ASTNode{
protected:
    std::string assemblyCode;
public:
    virtual ~ASTNode() = 0;
    ASTNode() = default;
    virtual void codeGenerate();
};

#endif 