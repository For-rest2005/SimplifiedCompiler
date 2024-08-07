#ifndef _SHARED_H_
#define _SHARED_H_
#include<iostream>
#include<string>

#define EMPTY 0
#define KEYWORD 1
#define IDENTIFIER 2
#define INTCONSTANT 3
#define OPERATOR 4
#define STRINGCONSTANT 5
#define SEMICOLON 6

inline void errorReport(const std::string& errorData){
    std::cerr << "ERROR:" << errorData << std::endl;
    exit(1);
}

#endif