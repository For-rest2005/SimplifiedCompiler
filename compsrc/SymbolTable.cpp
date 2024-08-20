#include "SymbolTable.h"

void LocalVarTable::exitScope(){
    addrTbl.pop_back();
    typeTbl.pop_back();
}
void LocalVarTable::enterScope(){
    addrTbl.push_back({});
    typeTbl.push_back({});
}
bool LocalVarTable::checkScope(std::string _str){
    return typeTbl.back().find(_str) != typeTbl.back().end();
}
std::pair<int,int> LocalVarTable::getVar(std::string _str){
    for(auto riter2 = addrTbl.rbegin(),riter1 = typeTbl.rbegin();riter1 != typeTbl.rend();riter1++,riter2++){
        if(riter1->find(_str) != riter1->end()){
            return {(*riter1)[_str],(*riter2)[_str]};
        }
    }
    return {-1,0};
}
bool LocalVarTable::empty(){return typeTbl.empty();}
void LocalVarTable::addVar(std::string _str,int _type,int _addr){
    typeTbl.back().insert({_str,_type});
    addrTbl.back().insert({_str,_addr});
}

std::pair<int,int> GlobalVarTable::getVar(std::string _str){
    if(typeTbl.find(_str) != typeTbl.end())
        return {typeTbl[_str],addrTbl[_str]};
    return {-1,0};
}
void GlobalVarTable::addVar(std::string _str,int _type,int _addr){
    typeTbl[_str] = _type;
    addrTbl[_str] = _addr;
}
bool GlobalVarTable::checkScope(std::string _str){
    return typeTbl.find(_str) != typeTbl.end();
}

void VarTable::exitScope(){local.enterScope();}
void VarTable::enterScope(){local.enterScope();}
bool VarTable::checkScope(std::string _str){return (local.empty()?global.checkScope(_str):local.checkScope(_str));}
std::pair<int,int> VarTable::getVar(std::string _str,bool &globalBit){
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
void VarTable::addVar(std::string _str,int _type,int _addr){
    if(local.empty()) global.addVar(_str,_type,_addr);
    else local.addVar(_str,_type,_addr);
}

