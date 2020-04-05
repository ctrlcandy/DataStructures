#include "LinkedList.h"

#include <cassert>
#include <stdexcept>

LinkedList::Node::Node(const ValueType& value, Node* prev, Node* next) :
        value(value), prev(prev), next(next) {};

LinkedList::Node::~Node()
{
	// ничего не удаляем, т.к. агрегация
}

void LinkedList::Node::insertNext(const ValueType& value)
{
	Node* newNode = new Node(value,this, this->next);
	this->next = newNode;
}

void LinkedList::Node::removeNext()
{
	Node* removeNode = this->next;
	Node* newNext = removeNode->next;
	delete removeNode;
	this->next = newNext;
    	newNext->prev = this;
}

LinkedList::LinkedList()
	: _head(nullptr), _tail(nullptr), _size(0) {}

LinkedList::LinkedList(const LinkedList& copyList)
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

LinkedList& LinkedList::operator=(const LinkedList& copyList)
{
	if (this == &copyList) {
		return *this;
	}
	LinkedList* bufList = new LinkedList(copyList);
	this->_size = bufList->_size;
	this->_head = bufList->_head;
    	this->_tail = bufList->_tail;

	return *this;
}

//Конструктор перемещения
LinkedList::LinkedList(LinkedList&& moveList) noexcept
{
	this->_size = moveList._size;
    	this->_tail = moveList._tail;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._tail = nullptr;
	moveList._head = nullptr;
}

//Перемещающий оператор присванивания
LinkedList& LinkedList::operator=(LinkedList&& moveList) noexcept
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

LinkedList::~LinkedList()
{
	forceNodeDelete(_head);
}

ValueType& LinkedList::operator[](const size_t pos) const
{
	return getNode(pos)->value;
}

LinkedList::Node* LinkedList::getNode(const size_t pos) const
{
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos >= this->_size) {
		assert(pos >= this->_size);
	}
	Node* bufNode = _head;
	for (int i = 0; i < pos; i++) {
		bufNode = bufNode->next;
	}

	return bufNode;
}

void LinkedList::insert(const size_t pos, const ValueType& value)
{
    if (pos < 0) {
        assert(pos < 0);
    }
    else if (pos > this->_size) {
        assert(pos > this->_size);
    }
    else if (pos == 0) {
        pushFront(value);
    }
    else {
        Node* bufNode = this->_head;
        for (size_t i = 0; i < pos-1; ++i) {
            bufNode = bufNode->next;
        }
        bufNode->insertNext(value);
        ++_size;
    }
}

void LinkedList::insertAfterNode(Node* node, const ValueType& value)
{
    node->insertNext(value);
    ++_size;
}

void LinkedList::pushBack(const ValueType& value)
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

void LinkedList::pushFront(const ValueType& value)
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

void LinkedList::removeFront()
{
    if (_head == nullptr)
        return;

    Node* temp = _head;
    _head = _head->next;
    delete temp;
    --_size;
}

void LinkedList::removeBack()
{
    if (_tail == nullptr)
        return;

    Node* temp = _tail;
    _tail = _tail->prev;
    delete temp;
    --_size;
}

void LinkedList::remove(const size_t pos)
{
    if (pos != 0) {
        Node* temp = _head;
        for (size_t i = 0; i < pos - 1; i++)
            temp = temp->next;

        Node* newNode = temp->next;
        temp->next = temp->next->next;
        delete newNode;
        --_size;
    }
    else
        removeFront();
}

void LinkedList::removeNextNode(Node* node)
{
    Node* currentDeleteNode = node->next;
    Node* currentNode = currentDeleteNode->next;
    node->next = currentNode;
    currentNode->prev = node;

    delete currentDeleteNode;
    --_size;
}

long long int LinkedList::findIndex(const ValueType& value) const
{
    Node* currentNode = _head;
    for (int i = 0; i < _size; ++i) {
        if (currentNode->value == value)
            return i;

        currentNode = currentNode->next;
    }

    throw std::out_of_range("Value is out of range");
}

LinkedList::Node* LinkedList::findNode(const ValueType& value) const
{
    Node* currentNode = _head;
    for (int i = 0; i < _size; ++i) {
        if (currentNode->value == value)
            return currentNode;

        currentNode = currentNode->next;
    }

    throw std::out_of_range("Value is out of range");
}

void LinkedList::reverse()
{
    Node* prev = nullptr;
    Node* next = nullptr;
    Node* curr = _head;

    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    _head = prev;
}

LinkedList LinkedList::reverse() const
{
    return getReverseList();
}

LinkedList LinkedList::getReverseList() const
{
    Node* prev = nullptr;
    Node* next = nullptr;
    Node* curr = this->_head;

    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    LinkedList* list = new LinkedList();
    list->_head = prev;
    list->_size = _size;

    return *list;
}

size_t LinkedList::size() const
{
	return _size;
}

void LinkedList::forceNodeDelete(Node* node)
{
	if (node == nullptr) 
		return;

	Node* nextDeleteNode = node->next;
	delete node;
	forceNodeDelete(nextDeleteNode);
}
