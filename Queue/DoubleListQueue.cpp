#include "DoubleListQueue.h"

void DoubleListQueue::enqueue(const ValueType &value) {
    this->pushBack(value);
}

void DoubleListQueue::dequeue() {
    this->removeFront();
}

const ValueType& DoubleListQueue::front() const {
    return (*this)[0];
}

bool DoubleListQueue::isEmpty() const {
    return DoubleLinkedList::size();
}

std::size_t DoubleListQueue::size() const {
    return DoubleLinkedList:size();
}
