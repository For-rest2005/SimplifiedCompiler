#ifndef _LEXER_H_
#define _LEXER_H_

#include <unordered_set>
#include <string>
#include "Shared.h"

#define EMPTY 0
#define KEYWORD 1
#define IDENTIFIER 2
#define INTCONSTANT 3
#define OPERATOR 4
#define STRINGCONSTANT 5
#define ENDPOINT -1

// inline int charTrans(char ch){return _charTrans[int(ch)];}

class Token{
private:
    int _type;
    std::string _value;
public:
    Token(int,const std::string&);
    Token() = default;
    int toInteger();
    const int type();
    const std::string value();
};

Token getToken();
void skipTokens(int n = 1);
void unGetToken(const Token&);

#endif