#include "ASTNode.h"

VarTable ASTNode::varEnvir{};
FunctionTable ASTNode::funEnvir{};

ASTNode::ASTNode():front(new Instruction()),back(front){}