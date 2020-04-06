#include "DoublyLinkedList.h"

#include <cassert>
#include <stdexcept>

DoublyLinkedList::Node::Node(const ValueType& value, Node* prev, Node* next) :
        value(value), prev(prev), next(next) {};

DoublyLinkedList::Node::~Node()
{
	// ничего не удаляем, т.к. агрегация
}

void DoublyLinkedList::Node::insertNext(const ValueType& value)
{
	Node* newNode = new Node(value,this, this->next);
	this->next = newNode;
}

void DoublyLinkedList::Node::removeNext()
{
	Node* removeNode = this->next;
	Node* newNext = removeNode->next;
	delete removeNode;
	this->next = newNext;
    newNext->prev = this;
}

DoublyLinkedList::DoublyLinkedList()
	: _head(nullptr), _tail(nullptr), _size(0) {}

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& copyList)
{
	_size = copyList._size;
	if (_size == 0) {
		_head = nullptr;
        _tail = nullptr;
		return;
	}

	_head = new Node(copyList._head->value);

	Node* currentNode = _head;
	Node* currentCopyNode = copyList._head;

	while (currentCopyNode->next) {
        currentCopyNode = currentCopyNode->next;
	currentNode->next = new Node(currentCopyNode->value, currentNode);
	currentNode = currentNode->next;
	}
	_tail = currentNode;
}

DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& copyList)
{
	if (this == &copyList) {
		return *this;
	}
	DoublyLinkedList* bufList = new DoublyLinkedList(copyList);
	this->_size = bufList->_size;
	this->_head = bufList->_head;
    	this->_tail = bufList->_tail;

	return *this;
}

//Конструктор перемещения
DoublyLinkedList::DoublyLinkedList(DoublyLinkedList&& moveList) noexcept
{
	this->_size = moveList._size;
    	this->_tail = moveList._tail;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._tail = nullptr;
	moveList._head = nullptr;
}

//Перемещающий оператор присванивания
DoublyLinkedList& DoublyLinkedList::operator=(DoublyLinkedList&& moveList) noexcept
{
	if (this == &moveList) {
		return *this;
	}
	forceNodeDelete(_head);
	this->_size = moveList._size;
	this->_tail = moveList._tail;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._tail = nullptr;
	moveList._head = nullptr;

	return *this;
}

DoublyLinkedList::~DoublyLinkedList()
{
	forceNodeDelete(_head);
}

ValueType& DoublyLinkedList::operator[](const size_t pos) const
{
	return getNode(pos)->value;
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(const size_t pos) const
{
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos >= this->_size) {
		assert(pos >= this->_size);
	}

	size_t halfSize = _size / 2;
    	Node* bufNode;

	if (pos < halfSize) {
	    bufNode = _head;
	    for (int i = 0; i < pos; i++)
		    bufNode = bufNode->next;
	}
	else {
        bufNode = _tail;
        for (int i = _size - 1; i > pos; i--)
            bufNode = bufNode->prev;
	}

	return bufNode;
}

void DoublyLinkedList::insert(const size_t pos, const ValueType& value)
{
    if (pos < 0) {
        assert(pos < 0);
    }
    else if (pos > this->_size) {
        assert(pos > this->_size);
    }

    if (pos == 0)
        pushFront(value);

    Node* bufNode = getNode(pos - 1);
    bufNode->insertNext(value);
    ++_size;

}

void DoublyLinkedList::insertAfterNode(Node* node, const ValueType& value)
{
    node->insertNext(value);
    ++_size;
}

void DoublyLinkedList::pushBack(const ValueType& value)
{
    Node* newNode = new Node(value, _tail);
    if (_tail != nullptr) {
        _tail->next = newNode;
    }
    else if (_head == nullptr) {
        _head = newNode;
    }
    _tail = newNode;
    ++_size;
}

void DoublyLinkedList::pushFront(const ValueType& value)
{
    Node* newNode = new Node(value, nullptr, _head);
    if (_head != nullptr) {
        _head->prev = newNode;
    }
    else if (_tail == nullptr) {
        _tail = newNode;
    }
    _head = newNode;
    ++_size;
}

void DoublyLinkedList::removeFront()
{
    if (_head == nullptr)
        return;

    Node* temp = _head;
    _head = _head->next;
    delete temp;
    --_size;
}

void DoublyLinkedList::removeBack()
{
    if (_tail == nullptr)
        return;

    Node* temp = _tail;
    _tail = _tail->prev;
    delete temp;
    --_size;
}

void DoublyLinkedList::remove(const size_t pos)
{
    if (pos == 0) {
        removeFront();
    }
    else if (pos == _size - 1) {
        removeBack();
    }
    else
    {
        Node* temp = getNode(pos - 1);

        Node* newNode = temp->next;
        temp->next = temp->next->next;
        delete newNode;
        --_size;
    }
}

void DoublyLinkedList::removeNextNode(Node* node)
{
    Node* currentDeleteNode = node->next;
    Node* currentNode = currentDeleteNode->next;
    node->next = currentNode;
    currentNode->prev = node;

    delete currentDeleteNode;
    --_size;
}

long long int DoublyLinkedList::findIndex(const ValueType& value) const
{
    Node* currentNode = _head;
    for (int i = 0; i < _size; ++i) {
        if (currentNode->value == value)
            return i;

        currentNode = currentNode->next;
    }
    throw std::out_of_range("Value is out of range");
}

DoublyLinkedList::Node* DoublyLinkedList::findNode(const ValueType& value) const
{
    Node* currentNode = _head;
    for (int i = 0; i < _size; ++i) {
        if (currentNode->value == value)
            return currentNode;

        currentNode = currentNode->next;
    }
    throw std::out_of_range("Value is out of range");
}

void DoublyLinkedList::reverse()
{
    Node* temp = _head;
    _head = _tail;
    _tail = temp;

    Node* curr = _head;
    while (curr != nullptr) {
        temp = curr->next;
        curr->next = curr->prev;
        curr->prev = temp;
        curr = curr->next;
    }
}

DoublyLinkedList DoublyLinkedList::reverse() const
{
    return getReverseList();
}

DoublyLinkedList DoublyLinkedList::getReverseList() const
{
    DoublyLinkedList list(*this);
    Node* temp = list._head;
    list._head = list._tail;
    list._tail = temp;

    Node* curr = list._head;
    while (curr != nullptr) {
        temp = curr->next;
        curr->next = curr->prev;
        curr->prev = temp;
        curr = curr->next;
    }

    return list;
}

size_t DoublyLinkedList::size() const
{
	return _size;
}

void DoublyLinkedList::forceNodeDelete(Node* node)
{
	if (node == nullptr) {
		return;
	}

	Node* nextDeleteNode = node->next;
	delete node;
	forceNodeDelete(nextDeleteNode);
}
