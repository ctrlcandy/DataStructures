#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <cstddef>

// потом поменяем на шаблоны
using ValueType = double;

class DoublyLinkedList
{
	// класс узла списка
	// по своей сути, может содержать любые данные,
	// можно реализовать и ассоциативный массив, просто добавив 
	// поле с ключем в узел и, с учетом этого, поменять методы DoublyLinkedList
	// (доступ по ключу, поиск по ключу и т.д.)
	struct Node {
        Node(const ValueType& value, Node* prev = nullptr, Node* next = nullptr);
	~Node();

	void insertNext(const ValueType& value);
	void removeNext();

        ValueType value;
        Node* prev;
	Node* next;
	};

public:
	////
	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList& copyList);
	DoublyLinkedList& operator=(const DoublyLinkedList& copyList);

	DoublyLinkedList(DoublyLinkedList&& moveList) noexcept;
	DoublyLinkedList& operator=(DoublyLinkedList&& moveList) noexcept;

	~DoublyLinkedList();
	////

	// доступ к значению элемента по индексу
    	ValueType& operator[](const size_t pos) const;
	// доступ к узлу по индексу
	DoublyLinkedList::Node* getNode(const size_t pos) const;
	
	// вставка элемента по индексу, сначала ищем, куда вставлять (О(n)), потом вставляем (O(1))
	void insert(const size_t pos, const ValueType& value);
	// вставка элемента после узла, (O(1))
	void insertAfterNode(Node* node, const ValueType& value);
	// вставка в конец (О(n))
	void pushBack(const ValueType& value);
	// вставка в начало (О(1))
	void pushFront(const ValueType& value);

	// удаление
    	void removeFront();
    	void removeBack();
	void remove(const size_t pos);
	void removeNextNode(Node* node);
	
	// поиск, О(n)
	long long int findIndex(const ValueType& value) const;
	Node* findNode(const ValueType& value) const;

	// разворот списка
	void reverse();					// изменение текущего списка
	DoublyLinkedList reverse() const;		// полчение нового списка (для константных объектов)
	DoublyLinkedList getReverseList() const;	// чтобы неконстантный объект тоже мог возвращать новый развернутый список

	size_t size() const;
private:
	Node*	_head;
    	Node*   _tail;
	size_t	_size;

	void forceNodeDelete(Node* node);
};

#endif //DOUBLYLINKEDLIST_H
