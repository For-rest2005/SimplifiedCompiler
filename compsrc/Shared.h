#ifndef _SHARED_H_
#define _SHARED_H_
#include "ASTNode.h"
#include "Expression.h"
#include "Lexer.h"
#include "Parser.h"
#include "Statement.h"
#include "SymbolTable.h"
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

#define ERRORTYPE -1
#define VOID 0
#define INTEGER 1
#define INTERGERARRAY 2

inline void errorReport(const std::string& errorData){
    std::cerr << "ERROR:" << errorData << std::endl;
    exit(1);
}

#endif