#include "ASTNode.h"

StackAllocator ASTNode::stackAlloc{};
StaticAllocator ASTNode::staticAlloc{};
VarTable ASTNode::varEnvir{};
FunctionTable ASTNode::funEnvir{};

ASTNode::ASTNode():front(new Instruction()),back(front){}