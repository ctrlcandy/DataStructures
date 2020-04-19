#include <stdexcept>
#include "VectorQueue.h"

VectorQueue::VectorQueue() : _backIndex(0), _queueCoef(1.5f) {};
VectorQueue::VectorQueue(const VectorQueue& copyVector) : MyVector(copyVector) {};

void VectorQueue::enqueue(const ValueType &value) {
    this->pushBack(value);
}

void VectorQueue::dequeue() {
    if (_backIndex == size()) {
        throw std::length_error("Incorrect operation");
    }
    _backIndex++;

    if ((float(size() - _backIndex) / capacity() <=  1/(_queueCoef * _queueCoef))) {
        MyVector bufVector(*this);
        this->clear();
        for (size_t i = _backIndex; i < bufVector.size(); i++) {
            this->pushBack(bufVector[i]);
        }
        _backIndex = 0;
    }

    //this->erase(0); - вариант проще
}

const ValueType &VectorQueue::front() const {
    if (_backIndex == size()) {
        throw std::length_error("Incorrect operation");
    }
    return (*this)[_backIndex];
}

bool VectorQueue::isEmpty() const {
    return !MyVector::size();
}

std::size_t VectorQueue::size() const {
    return  MyVector::size();
}



