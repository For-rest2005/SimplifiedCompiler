#include "MemoryAllocator.h"

const int StackAllocator::top(){
    return st.top();
}
int StackAllocator::alloc(int _size){
    st.top() += _size;
    return st.top()-_size;
    //The address this function returns should be different for local array and global array
}
void StackAllocator::dealloc(int _size = 1){
    st.top() -= _size;
}
void StackAllocator::enterNewFunction(){
    st.push(1);    
}
void StackAllocator::exitFunction(){
    st.pop();
}

int StaticAllocator::alloc(int _size){
    top += _size;
    return top-_size;
}
StaticAllocator::StaticAllocator():top(1){}
