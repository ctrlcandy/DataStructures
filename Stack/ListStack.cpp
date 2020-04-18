#include "ListStack.h"

void ListStack::push(const ValueType &value) {
    this->pushBack(value);
}

void ListStack::pop() {
    this->removeBack();
}

const ValueType &ListStack::top() const {
    return (*this)[LinkedList::size() - 1];
}

bool ListStack::isEmpty() const {
    return LinkedList::size();
}

std::size_t ListStack::size() const {
    return LinkedList::size();
}

