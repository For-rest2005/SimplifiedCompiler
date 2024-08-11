#include "Lexer.h"
using namespace std;

string tbl[] = {"EMPTY","KEYWORD","IDENTIFIER","INTCONSTANT","OPERATOR","STRINGCONSTANT","SEMICOLON"};

int main(){
    Token curToken;
    freopen("test.txt","r",stdin);
    while((curToken = getToken()).type() != ENDPOINT){
        cout << tbl[curToken.type()] << ' ' << curToken.value() << endl;
    }
    return 0;
}