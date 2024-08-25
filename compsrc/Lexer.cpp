#include "Lexer.h"

const static std::unordered_set<std::string> theOperator = {"==","<=",">=","&&","||","<<",">>"};
const static std::unordered_set<std::string> theKeyword = {"if","else","while","int","string","putchar","print","read","return","break","continue"};
const static int _charType[128] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,2,2,2,2,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,3,3,3,-1,3,3,3,3,3,3,3,3,3,-1,3,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,-1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,-1,3,3,4,-1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,3,3,3,-1};
inline int charTypeGet(char ch){return _charType[int(ch)];}

#define DIGIT 1
#define SPACE 2
#define SYMBOL 3
#define LETTER 4
#define INVALID -1

Token::Token(int __type,const std::string &__value):_type(__type),_value(__value){}
const std::string Token::value(){return _value;}
const int Token::type(){return _type;}
int Token::toInteger(){
    if(_type != INTCONSTANT) errorReport("Invalid integer");
    int cnt = 0;
    for(int i = (int)_value.size()-1,tmp = 1;i >= 0;i--,tmp = tmp*10)
        cnt += tmp*(_value[i]-'0');
    return cnt;
}

Token getStringConstant(){
    static std::unordered_map<char,char> charTrans = {{'n','\n'},{'\\','\\'},{'"','"'}};
    char ch;
    std::string buffer;
    while(true){
        ch = getchar();
        if(ch == EOF) errorReport("Incomplete string");
        if(ch == '\\'){
            ch = getchar();
            buffer.push_back(charTrans[ch]);
            continue;
        }
        if(ch == '"')
            break;
        buffer.push_back(ch);
    }
    return Token(STRINGCONSTANT,buffer);
}

static std::stack<Token> getTokenBuffer;

Token getToken(){
    if(!getTokenBuffer.empty()){
        Token top = getTokenBuffer.top();
        getTokenBuffer.pop();
        if(top.type() == -1) exit(1);
        return top;
    }
    char ch;
    int type;
    std::string buffer;
    ch = getchar();
    while(charTypeGet(ch) == SPACE)
        ch = getchar();
    if(ch == EOF) return Token(ENDPOINT,"");
    if(ch == '"') return getStringConstant();
    if(ch == ';') return Token(SEMICOLON,";");
    buffer.push_back(ch);
    if(charTypeGet(ch) == DIGIT){
        type = INTCONSTANT;
        while(true){
            ch = getchar();
            if(charTypeGet(ch) == LETTER){
                errorReport("Invalid integer");
            }else if(charTypeGet(ch) == SYMBOL || charTypeGet(ch) == SPACE){
                ungetc(ch,stdin);
                type = INTCONSTANT;
                break;
            }
            buffer.push_back(ch);
        }
    }
    else if(charTypeGet(ch) == LETTER){
        while(true){
            ch = getchar();
            if(charTypeGet(ch) == SYMBOL || charTypeGet(ch) == SPACE){
                ungetc(ch,stdin);
                if(theKeyword.find(buffer) != theKeyword.end())
                    type = KEYWORD;
                else
                    type = IDENTIFIER;
                break;
            }
            buffer.push_back(ch);
        }
    }else if(charTypeGet(ch) == SYMBOL){
        type = OPERATOR;
        ch = getchar();
        if(theOperator.find(buffer+ch) != theOperator.end()){
            buffer.push_back(ch);
        }else{
            ungetc(ch,stdin);
        }
    }else if(charTypeGet(ch) == INVALID){
        errorReport("Invalid character");
    }
    std::cerr << type << ' ' << buffer << std::endl;
    return Token(type,buffer);
}

void skipTokens(int n){
    while(n--) getToken();
}

void unGetToken(const Token &obj){
    getTokenBuffer.push(obj);
}