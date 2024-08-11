#include "Parser.h"

static Lexer lexer;

Statement* parser(){
    Statement *program = new Statement(getStatement());
    return program;
}

Statement* getStatement(){
    Statement* curStatement;
    lexer.fetchToken();
    
    
    return curStatement;
}