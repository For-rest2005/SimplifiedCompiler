#include "SymbolTable.h"

void LocalVarTable::exitScope(){
    addrTbl.pop_back();
    typeTbl.pop_back();
    curAddr.pop_back();
}
void LocalVarTable::enterScope(){
    addrTbl.push_back({});
    typeTbl.push_back({});
    curAddr.push_back(1);
}
bool LocalVarTable::checkScope(std::string _str){
    return typeTbl.back().find(_str) != typeTbl.back().end();
}
std::pair<int,unsigned int> LocalVarTable::fetchVar(std::string _str){
    for(auto riter2 = addrTbl.rbegin(),riter1 = typeTbl.rbegin();riter1 != typeTbl.rend();riter1++,riter2++){
        if(riter1->find(_str) != riter1->end()){
            return {(*riter1)[_str],(*riter2)[_str]};
        }
    }
    return {-1,0};
}
bool LocalVarTable::empty(){return typeTbl.empty();}
void LocalVarTable::addSymbol(std::string _str,int _type,int _size = 1){
    typeTbl.back()[_str] = _type;
    addrTbl.back()[_str] = curAddr.back();
    curAddr.back() += _size;
}

std::pair<int,unsigned int> GlobalVarTable::fetchVar(std::string _str){
    if(typeTbl.find(_str) != typeTbl.end())
        return {typeTbl[_str],addrTbl[_str]};
    return {-1,0};
}
void GlobalVarTable::addSymbol(std::string _str,int _type,int _size = 1){
    typeTbl[_str] = _type;
    addrTbl[_str] = curAddr;
    curAddr += _size;
}
bool GlobalVarTable::checkScope(std::string _str){
    return typeTbl.find(_str) != typeTbl.end();
}

void VarTable::exitScope(){local.enterScope();}
void VarTable::enterScope(){local.enterScope();}
bool VarTable::checkScope(std::string _str){return (local.empty()?global.checkScope(_str):local.checkScope(_str));}
std::pair<int,unsigned int> VarTable::fetchVar(std::string _str,bool &globalBit){
    std::pair<int,unsigned int> varData = local.fetchVar(_str);
    if(varData.first != -1){
        globalBit = 0;
        return varData;
    }
    varData = global.fetchVar(_str);
    if(varData.first != -1){
        globalBit = 1;
        return varData;
    }
    return {-1,0};
}
void VarTable::addSymbol(std::string _str,int _type,int _size = 1){
    if(local.empty()) global.addSymbol(_str,_type,_size);
    else local.addSymbol(_str,_type,_size);
}


