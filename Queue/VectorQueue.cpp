#include "VectorQueue.h"

void VectorQueue::enqueue(const ValueType &value) {
    this->pushBack(value);
}

void VectorQueue::dequeue() {
    this->erase(0);
}

const ValueType &VectorQueue::front() const {
    return (*this)[0];
}

bool VectorQueue::isEmpty() const {
    return MyVector::size();
}

std::size_t VectorQueue::size() const {
    return  MyVector::size();
}



