#ifndef _SHARED_H_
#define _SHARED_H_
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <iostream>
#include <functional>
#include <algorithm>

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

extern int lineNum;
extern int charNum;
extern std::string fileName;

inline void errorReport(const std::string& errorData){
    std::cerr << "ERROR:At" << fileName << ' ' << "Line:" << lineNum << ' ' << charNum << "-th character" << std::endl
    << errorData << std::endl;
    exit(1);
}

#endif