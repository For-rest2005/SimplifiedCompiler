#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_
#include "Shared.h"
#include <vector>
#include <unordered_map>

class LocalVarTable{
private:
    std::vector<std::unordered_map<std::string,int>> addrTbl;
    std::vector<std::unordered_map<std::string,int>>typeTbl;
    std::vector<unsigned int> curAddr;
public:
    void addSymbol(std::string,int,int);
    std::pair<int,unsigned int> fetchVar(std::string);//return datetype,addr
    bool empty();
    bool checkScope(std::string);
    void enterScope();
    void exitScope();
};


class GlobalVarTable{
private:
    std::unordered_map<std::string,int> addrTbl;
    std::unordered_map<std::string,int> typeTbl;
    unsigned int curAddr;
public:
    void addSymbol(std::string,int,int);
    std::pair<int,unsigned int> fetchVar(std::string);
    bool checkScope(std::string);
};
//You need to realize that local varibles only have relative memory address while global varibles have absolute address

class VarTable{
private:
    GlobalVarTable global;
    LocalVarTable local;
public:
    void addSymbol(std::string,int,int);
    std::pair<int,unsigned int> fetchVar(std::string,bool&);
    bool checkScope(std::string);
    void enterScope();
    void exitScope();
};

class FunctionTable{
};

#endif