#include "ListQueue.h"

ListQueue::ListQueue(const ListQueue &copyList) {
    for (size_t i = 0; i < copyList.size(); ++i) {
        this->pushBack(copyList[i]);
    }
}

void ListQueue::enqueue(const ValueType &value) {
    this->pushBack(value);
}

void ListQueue::dequeue() {
    this->removeFront();
}

const ValueType &ListQueue::front() const {
    return (*this)[0];
}

bool ListQueue::isEmpty() const {
    return LinkedList::size();
}

std::size_t ListQueue::size() const {
    return LinkedList::size();
}

