#ifndef _SHARED_H_
#define _SHARED_H_
#include "Lexer.h"
#include "ASTNode.h"
#include "Expression.h"
#include "Statement.h"
#include "SymbolTable.h"
#include "Instruction.h"
#include "FakeLinker.h"
#include <stack>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <iostream>
#include <functional>

#define EMPTY 0
#define KEYWORD 1
#define IDENTIFIER 2
#define INTCONSTANT 3
#define OPERATOR 4
#define STRINGCONSTANT 5
#define SEMICOLON 6

#define DATATYPE_ERRORTYPE -1
#define DATATYPE_VOID 0
#define DATATYPE_INT 1
#define DATATYPE_INTPOINTER 2
#define DATATYPE_STRINGCONSTANT 3

inline void errorReport(const std::string& errorData){
    std::cerr << "ERROR:" << errorData << std::endl;
    exit(1);
}

#endif