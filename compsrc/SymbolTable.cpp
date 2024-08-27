#include "SymbolTable.h"

#define HEAPTOP 200

void LocalVarTable::exitScope(){
    curAddr.pop();
    varTbl.pop_back();
}
void LocalVarTable::enterScope(){
    if(curAddr.empty()) curAddr.push(1);
    else curAddr.push(curAddr.top());
    varTbl.push_back({});
}
bool LocalVarTable::checkScope(const std::string& _str){
    return varTbl.back().find(_str) != varTbl.back().end();
}
std::pair<int,int> LocalVarTable::getVar(const std::string& _str){
    for(auto it = varTbl.rbegin();it != varTbl.rend();it++){
        if(it->find(_str) != it->end())
            return (*it)[_str];
    }
    return {-1,0};
}
bool LocalVarTable::empty(){return varTbl.empty();}
int LocalVarTable::addVar(const std::string& _str,int _type,int _size){
    varTbl.back().insert({_str,{_type,curAddr.top()+_size-1}});
    curAddr.top() += _size;
    return curAddr.top()-1;
}

std::pair<int,int> GlobalVarTable::getVar(const std::string& _str){
    if(varTbl.find(_str) != varTbl.end())
        return varTbl[_str];
    return {-1,0};
}
int GlobalVarTable::addVar(const std::string& _str,int _type,int _size){
    varTbl.insert({_str,{_type,curAddr}});
    curAddr += _size;
    return curAddr-_size;
}
bool GlobalVarTable::checkScope(const std::string& _str){
    return varTbl.find(_str) != varTbl.end();
}
GlobalVarTable::GlobalVarTable():curAddr(HEAPTOP){}

void VarTable::exitScope(){local.exitScope();}
void VarTable::enterScope(){local.enterScope();}
bool VarTable::checkScope(const std::string& _str){return (local.empty()?global.checkScope(_str):local.checkScope(_str));}
std::pair<int,int> VarTable::getVar(const std::string& _str,bool &globalBit){
    std::pair<int,int> varData = local.getVar(_str);
    if(varData.first != -1){
        globalBit = 0;
        return varData;
    }
    varData = global.getVar(_str);
    if(varData.first != -1){
        globalBit = 1;
        return varData;
    }
    return {-1,0};
}
int VarTable::addVar(const std::string& _str,int _type,int _size = 1){
    if(checkScope(_str))
        errorReport("Redefine variable "+_str);
    if(local.empty()) return global.addVar(_str,_type,_size);
    else return local.addVar(_str,_type,_size);
}

void FunctionTable::addFun(const std::string& _str,const FunctionData& funData){
    // Error may occur here
    funTbl[_str] = funData;
}

FunctionData::FunctionData(int _returnType,const std::vector<std::pair<int,std::string>>& _arguments)
:returnType(_returnType),arguments(_arguments){}
FunctionData FunctionTable::getFun(const std::string& _str){
    // Error may occur here
    return funTbl.at(_str);
}
FunctionData::FunctionData(const FunctionData& obj){
    returnType = obj.returnType;
    arguments = obj.arguments;
}


