#ifndef _SHARED_H_
#define _SHARED_H_
#include<iostream>
#include<string>

inline void errorReport(const std::string& errorData){
    std::cerr << "ERROR:" << errorData << std::endl;
    exit(1);
}

#endif