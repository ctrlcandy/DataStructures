#include "ListStack.h"

ListStack::ListStack(const ListStack &copyList) {
    for (size_t i = 0; i < copyList.size(); ++i) {
        this->pushFront(copyList[i]);
    }
}

void ListStack::push(const ValueType &value) {
    this->pushFront(value);
}

void ListStack::pop() {
    this->removeFront();
}

const ValueType &ListStack::top() const {
    return (*this)[0];
}

bool ListStack::isEmpty() const {
    return LinkedList::size();
}

std::size_t ListStack::size() const {
    return LinkedList::size();
}


