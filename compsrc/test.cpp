#include "Lexer.h"
using namespace std;

string tbl[] = {"EMPTY","KEYWORD","IDENTIFIER","INTCONSTANT","OPERATOR","STRINGCONSTANT","SEMICOLON"};

int main(){
    Lexer tmp;
    freopen("test.txt","r",stdin);
    while(tmp.fetchToken()){
        cout << tbl[tmp.curToken.type()] << ' ' << tmp.curToken.value() << endl;
    }
    return 0;
}