#include "Statement.h"
using namespace std;

void FunctionCall::print(){
    cout << "functioncall:" << name << endl;
    for(int i = 0;i < arguments.size();i++){
        cout << "argument" << i << ":";
        arguments[i]->print();
    }
}
 
void VariableExp::print(){
    cout << "variable:" << name << endl;
}

void ArrayExp::print(){
    cout << "array:" << name << endl;
    cout << "size:";
    index->print();
}

void ConstantExp::print(){
    cout << "constant:" << value << endl;
}

void UnaryOp::print(){
    cout << "op " << op << endl;
    first->print();
}

void BinaryOp::print(){
    cout << "op " << op << endl;
    first->print();
    second->print();
}

void TernaryOp::print(){
    cout << "op " << op << endl;
    first->print();
    second->print();
    third->print();
}

