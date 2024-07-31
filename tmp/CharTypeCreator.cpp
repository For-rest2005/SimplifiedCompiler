#include "Lexer.h"
using namespace std;

inline bool isdigit(char ch){ return ch >= 48 && ch <= 57;}
inline bool ischaracter(char ch){return (ch >= 97 && ch <= 122) || (ch >= 65 &&  ch <= 90);}
unordered_set<char> tbl = {'~','!','#','%','^','&','*','(',')','-','+','=','{','}','|',':','\'',':',';','"','<',',','>','?','/'}; 

int tmp1[128],tmp2[128];

void print(int *tmp){
    cout << '{';
    for(int i = 0;i < 128;i++){
        cout << tmp[i];
        if(i != 127) cout << ',';
    }
    cout << '}' << '\n';
}

int main(){
    for(int i = 0;i < 128;i++){
        if(i >= 48 && i <= 57){
            tmp1[i] = DIGIT;
            tmp2[i] = i-48+1;
        }
        else if(i >= 97 && i <= 122){
            tmp1[i] = LETTER;
            tmp2[i] = 10+i-97+1;
        }else if((i >= 65 && i <= 90) || (i == '_')){
            tmp1[i] = LETTER;
            tmp2[i] = 36+i-65+1;
        }else if(isspace(i)){
            tmp1[i] = SPACE;
            tmp2[i] = -1;
        }else if(tbl.find(i) != tbl.end()){
            tmp1[i] = SYMBOL;
            tmp2[i] = -1;
        }else{
            tmp1[i] = INVALID;
            tmp2[i] = -1;
        }
    }
    print(tmp1);
    print(tmp2);
}