#ifndef _FAKELINKER_H_
#define _FAKELINKER_H_
#include "Shared.h"
#include "Instruction.h"
#include "Parser.h"
#include "ASTNode.h"
#include "Expression.h"
#include "Statement.h"
extern std::unordered_map<std::string,Instruction*> labelPos;
extern std::unordered_map<Instruction*,std::string> jmpLabel;
extern std::unordered_map<Instruction*,Instruction*> jmpInstr;
extern std::vector<Instruction*> breakJmp;
extern std::vector<Instruction*> continueJmp;

void linker();

#endif