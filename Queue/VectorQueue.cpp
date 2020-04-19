#include "VectorQueue.h"

VectorQueue::VectorQueue(const VectorQueue &copyVector) : VectorQueue() {
    for (size_t i = 0; i < copyVector.size(); ++i) {
        this->pushBack(copyVector[i]);
    }
}

void VectorQueue::enqueue(const ValueType &value) {
    this->pushBack(value);
}

void VectorQueue::dequeue() {
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
    return (*this)[_backIndex];
}

bool VectorQueue::isEmpty() const {
    return MyVector::size();
}

std::size_t VectorQueue::size() const {
    return  MyVector::size();
}



