#include "Lexer.h"
#include "Shared.h"

Token::Token(int __type,const std::string &__value):_type(__type),_value(__value){}

const std::string Token::value(){return _value;}

const int Token::type(){return _type;}

bool Lexer::fetchToken(){
    char ch;
    while(true){
        if(checkBit){
            checkBit = 0;
            return 1;
        }
        ch = getchar();
        if(ch == EOF){
            clearBuffer();
            return 0;
        }
        switch (charTypeGet(ch))
        {
        case CHARSEMICOLON:
            clearBuffer();
            buffer.push_back(ch);
            currentType = SEMICOLON;
            break;
        case SPACE:
            clearBuffer();
            break;
        case SYMBOL:
            if(ch == '"'){
                clearBuffer();
                stringConstantTake();//buffer without '"'
                continue;
            }else if(currentType == IDENTIFIER || currentType == INTCONSTANT){
                clearBuffer();
                buffer.push_back(ch);
                currentType = OPERATOR;
            }else if(currentType == EMPTY){
                buffer.push_back(ch);
                currentType = OPERATOR;
            }else if(currentType == OPERATOR || currentType == SEMICOLON){
                if(theOperator.find(buffer+ch) != theOperator.end()){
                    buffer.push_back(ch);
                    clearBuffer();
                }else{
                    clearBuffer();
                    buffer.push_back(ch);
                    currentType = OPERATOR;
                }
            }
            break;
        case DIGIT:
            if(currentType == INTCONSTANT || currentType == IDENTIFIER){
                buffer.push_back(ch);
            }
            else if(currentType == EMPTY){
                buffer.push_back(ch);
                currentType = INTCONSTANT;
            }
            else if(currentType == OPERATOR || currentType == SEMICOLON){
                clearBuffer();
                buffer.push_back(ch);
                currentType = INTCONSTANT;
            }
            break;
        case LETTER:
            if(currentType == INTCONSTANT){
                errorReport("Invalid identifier name");
            }
            else if(currentType == IDENTIFIER){
                buffer.push_back(ch);
            }else if(currentType == OPERATOR || currentType == SEMICOLON){
                clearBuffer();
                buffer.push_back(ch);
                currentType = IDENTIFIER;
            }else if(currentType == EMPTY){
                buffer.push_back(ch);
                currentType = IDENTIFIER;
            }
            break;
        case INVALID:
            errorReport("Invalid character");
            break;
        }
    }
}

void Lexer::clearBuffer(){
    if(currentType == EMPTY) return ;
    if(currentType == IDENTIFIER && theKeyword.find(buffer) != theKeyword.end())
        curToken = Token(KEYWORD,buffer);
    else
        curToken = Token(currentType,buffer);
    checkBit = 1;
    buffer.clear();
    currentType = EMPTY;
}

void Lexer::stringConstantTake(){
    currentType = STRINGCONSTANT;
    char ch;
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
    clearBuffer();
}

Lexer::Lexer():curToken(0,""),currentType(EMPTY),checkBit(0),buffer(""){}

