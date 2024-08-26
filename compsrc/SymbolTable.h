#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_
#include "Shared.h"

// These symbol tables are only used in the codegeneration process

class LocalVarTable{
private:
    std::vector<std::unordered_map<std::string,std::pair<int,int>>> varTbl;
    // The first part is data type, the second part is variable address
    std::stack<int> curAddr;
    // The top of curAddr always points to the next place of the stack
public:
    bool checkScope(const std::string&);
    void addVar(const std::string&,int,int);
    std::pair<int,int> getVar(const std::string&);
    bool empty();
    void enterScope();
    void exitScope();
};

class GlobalVarTable{
private:
    std::unordered_map<std::string,std::pair<int,int>> varTbl;
    int curAddr;
public:
    bool checkScope(const std::string&);
    void addVar(const std::string&,int,int);
    std::pair<int,int> getVar(const std::string&);
};
//You need to realize that local varibles only have relative memory address while global varibles have absolute address
class VarTable{
private:
    GlobalVarTable global;
    LocalVarTable local;
public:
    void addVar(const std::string&,int,int);
    std::pair<int,int> getVar(const std::string&,bool&);
    //return {datetype,addr}
    //We ensure that the datatype getVar() returns is a "var" type
    bool checkScope(const std::string&);
    void enterScope();
    void exitScope();
};

class FunctionData{
public:
    int returnType;
    std::vector<std::pair<int,std::string>> arguments;
    FunctionData(int,const std::vector<std::pair<int,std::string>>&);
};

class FunctionTable{
protected:
    //Each function has its return type, name and its arguments(including data type and name)
    std::unordered_map<std::string,FunctionData> funTbl;
public:
    FunctionTable() = default;
    FunctionData getFun(const std::string&);
    void addFun(const std::string&,const FunctionData&);
};

#endif