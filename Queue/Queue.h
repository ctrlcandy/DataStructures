#pragma once
// Уровень абстракции
// клиентский код подключает именно этот хедер

// тип значений в стеке
#include <cstddef>
#include "QueueImplementation.h"

using ValueType = double;

// на основе какого контейнера работает стек
enum class StackContainer {
	Vector = 0,
	List,
	DoubleList,
	// можно дополнять другими контейнерами
};

class Queue
{
public:
	// Большая пятерка
	Queue(StackContainer container = StackContainer::Vector);
	// элементы массива последовательно подкладываются в стек
	Queue(const ValueType* valueArray, std::size_t arraySize,
          StackContainer container = StackContainer::Vector);

	Queue(const Queue& copyStack);
	Queue& operator=(const Queue& copyStack);

	// Здесь как обычно
	Queue(Queue&& moveStack) noexcept;
	Queue& operator=(Queue&& moveStack) noexcept;

	~Queue();

	// добавление в хвост
	void enqueue(const ValueType& value);
	// удаление с хвоста
	void dequeue();
	// посмотреть элемент в хвосте
	const ValueType& front() const;
	// проверка на пустоту
	bool isEmpty() const;
	// размер 
	size_t size() const;
private:
	// указатель на имплементацию (уровень реализации)
	QueueImplementation* _pimpl = nullptr;
	// тип контейнера, наверняка понадобится
	StackContainer _containerType;
};

