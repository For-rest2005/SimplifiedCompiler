#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_
#include <stack>
#include <string>
#include <utility>

class SymbolTable{
private:
    std::stack<std::pair<std::string,int>> symtbl;
public:
    void addLocalSymbol(std::string);
    //addSymbol(x),checkScope(x),findSymbol(x)
    void removeSymbol();
    void enterScope();
    void exitScope();
    
};
//Here you need to realize that local varibles only have relative memory address.
#endif