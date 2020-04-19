#include "VectorStack.h"

void VectorStack::push(const ValueType &value) {
    this->pushBack(value);
}

void VectorStack::pop() {
    this->popBack();
}

const ValueType &VectorStack::top() const {
    return (*this)[size()-1];
}

bool VectorStack::isEmpty() const {
    return !MyVector::size();
}

std::size_t VectorStack::size() const {
    return  MyVector::size();
}




