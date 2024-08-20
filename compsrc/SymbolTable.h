#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_
#include "Shared.h"

class LocalVarTable{
private:
    std::vector<std::unordered_map<std::string,int>> addrTbl;
    std::vector<std::unordered_map<std::string,int>>typeTbl;
    std::vector<int> curAddr;
public:
    void addVar(std::string,int,int);
    std::pair<int,int> getVar(std::string);
    bool empty();
    bool checkScope(std::string);
    void enterScope();
    void exitScope();
};

class GlobalVarTable{
private:
    std::unordered_map<std::string,int> addrTbl;
    std::unordered_map<std::string,int> typeTbl;
    int curAddr;
public:
    void addVar(std::string,int,int);
    std::pair<int,int> getVar(std::string);
    bool checkScope(std::string);
};
//You need to realize that local varibles only have relative memory address while global varibles have absolute address
class VarTable{
private:
    GlobalVarTable global;
    LocalVarTable local;
public:
    void addVar(std::string,int,int);
    std::pair<int,int> getVar(std::string,bool&);
    //return {datetype,addr}
    //We ensure that the datatype getVar() returns is a "var" type
    bool checkScope(std::string);
    void enterScope();
    void exitScope();
};

class FunctionTable{

};

#endif