#include "FakeLinker.h"

std::unordered_map<std::string,Instruction*> labelPos;
std::unordered_map<Instruction*,std::string> jmpLabel;
std::unordered_map<Instruction*,Instruction*> jmpInstr;
std::vector<Instruction*> breakJmp;
std::vector<Instruction*> continueJmp;