#ifndef _MEMORYALLOCATOR_H_
#define _MEMORYALLOCATOR_H_
#include "Shared.h"

class StackAllocator{
private:
    std::stack <int> st;
public:
    const int top();
    int alloc(int);
    void dealloc(int);
    void enterNewFunction();
    void exitFunction();
    StackAllocator() = default;
};

class StaticAllocator{
private:
    int top;
public:
    int alloc(int);
    StaticAllocator();
};

#endif 