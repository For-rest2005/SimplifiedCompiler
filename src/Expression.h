#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_
#include "ASTNode.h"

class Expression:public ASTNode{
protected:
    int _datatype;
    unsigned int _memoryAddress;
};

#endif
