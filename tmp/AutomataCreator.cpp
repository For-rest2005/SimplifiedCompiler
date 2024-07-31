#include "Lexer.h"
using namespace std;
constexpr int NAX = 1e4+10;
constexpr int NEXTN = 63;

std::vector<std::string> theKeyword = {"if","else","while","var","output","read","def","return"};
int status[NAX][NEXTN];
int stN = 10;
//status[k][0] represents the type fo the k-th status

inline bool isdigit(char ch){return (ch >= 1 && ch <= 10);}
inline bool isletter(char ch){return !isdigit(ch);}

void insert(string str){
    int cur = 0;
    for(auto c:str){
        if(status[cur][charTrans(c)] == -1){
            status[cur][charTrans(c)] = ++stN;
            status[cur][0] = IDENTIFIER;
        }
        cur = status[cur][charTrans(c)];
    }
    status[cur][0] = KEYWORD;
}

void test(string s){
    int cur = 0;
    for(auto c:s){
        cur = status[cur][charTrans(c)];
        if(cur == -1){
            cout << "lexer error";
            return;
        }
    }
    cout << s << "type:" << status[cur][0];
}

int main(){
    for(int i = 0;i < NAX;i++)
        for(int j = 1;j < NEXTN;j++)
            status[i][j] = -1;
    status[EMPTY][0] = EMPTY;
    status[IDENTIFIER][0] = IDENTIFIER;
    status[NUMBER][0] = NUMBER;
    for(auto tmp:theKeyword)
        insert(tmp);
    for(int j = 1;j < NEXTN;j++){
        if(isdigit(j)) status[EMPTY][j] = NUMBER;
        else if(status[EMPTY][j] == -1) status[EMPTY][j] = IDENTIFIER;
    }
    for(int j = 1;j < NEXTN;j++)
        status[IDENTIFIER][j] = IDENTIFIER;
    for(int j = 1;j <= 10;j++ )
        status[NUMBER][j] = NUMBER;
    cout << '{' << '\n';
    for(int i = 0;i <= stN;i++){
        cout << '{';
        for(int j = 0;j < NEXTN;j++){
            cout << status[i][j];
            if(j != NEXTN-1) cout << ',';
        }
        cout << '}' << '\n';
    }
    cout << '}' << '\n';
    string s;
    cin >> s;
    test(s);
    return 0;
}