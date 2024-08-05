#include "Lexer.h"
#include "SemanticAnalyzer.h"
#include "Parser.cpp"
#include "CodeGenerator.h"
using namespace std;

string tbl[] = {"EMPTY","KEYWORD","IDENTIFIER","NUMBER","OPERATOR","STRINGCONSTANT"};

int main(){
    Lexer tmp;
    
    freopen("test.txt","r",stdin);
    tmp.init();
    for(auto cur:tmp.data){
        cout << tbl[cur.type] << ' ' << cur.value << endl;
    }
    return 0;
}