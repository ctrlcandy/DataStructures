#include "VectorStack.h"

VectorStack::VectorStack(const VectorStack &copyVector) {
    for (size_t i = 0; i < copyVector.size(); ++i) {
        this->pushBack(copyVector[i]);
    }
}

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




