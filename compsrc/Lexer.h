#ifndef _LEXER_H_
#define _LEXER_H_

#include<string>
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<ctype.h>
#include<iostream>

#define EMPTY 0
#define KEYWORD 1
#define IDENTIFIER 2
#define INTCONSTANT 3
#define OPERATOR 4
#define STRINGCONSTANT 5

#define DIGIT 1
#define SPACE 2
#define SYMBOL 3
#define LETTER 4
#define CHARSEMICOLON 5
#define INVALID -1

static std::unordered_set<std::string> theOperator = {"==","<=",">=",">>","<<","&&","||","!="};
static std::unordered_set<std::string> theKeyword = {"if","else","while","int","string","putchar","read","return","break","continue"};

static int _charType[128] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,2,2,2,2,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,3,3,3,-1,3,3,3,3,3,3,3,3,3,-1,3,1,1,1,1,1,1,1,1,1,1,3,5,3,3,3,3,-1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,-1,-1,-1,3,4,-1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,3,3,3,-1};
static std::unordered_map<char,char> charTrans = {{'n','\n'},{'\\','\\'},{'"','"'}};

inline int charTypeGet(char ch){return _charType[int(ch)];}
// inline int charTrans(char ch){return _charTrans[int(ch)];}


class Token{
private:
    int _type;
    std::string _value;
public:
    Token(int,const std::string&);
    Token() = default;
    const int type();
    const std::string value();
};

class Lexer{
private:
    std::string buffer;
    int currentType;//Using enum type here is safer
    bool checkBit;

    void clearBuffer();
    void stringConstantTake();
public:
    Lexer();
    bool fetchToken();
    Token curToken;
};

#endif