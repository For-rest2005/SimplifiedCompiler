#include "Lexer.h"
#include "Shared.h"

Token::Token(int _type,const std::string &_value):type(_type),value(_value){}

void Lexer::init(){
    char ch;
    while(true){
        ch = getchar();
        if(ch == EOF){
            clearBuffer();
            break;
        }
        // std::cerr << ch << ' ' << charTypeGet(ch) << ' ' << currentType << ' ' << buffer << std::endl;
        switch (charTypeGet(ch))
        {
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
            }else if(currentType == OPERATOR){
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
            else if(currentType == OPERATOR){
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
            }else if(currentType == OPERATOR){
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
    if(buffer.empty()) return ;
    if(currentType == IDENTIFIER && theKeyword.find(buffer) != theKeyword.end())
        data.push_back(Token(KEYWORD,buffer));
    else
        data.push_back(Token(currentType,buffer));
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
    clearBuffer();;
}

