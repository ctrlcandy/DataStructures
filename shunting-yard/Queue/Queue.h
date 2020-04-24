#pragma once
// Уровень абстракции
// клиентский код подключает именно этот хедер

#include <cstddef>
#include "../Tokens/Token.h"

// тип значений в стеке
using ValueType = Token;

// на основе какого контейнера работает стек
enum class QueueContainer {
    Vector = 0,
    List,
    DoubleList,
    // можно дополнять другими контейнерами
};

// декларация класса с реализацией
class QueueImplementation;

class Queue
{
public:
	// Большая пятерка
	Queue(QueueContainer container = QueueContainer::Vector);
	// элементы массива последовательно подкладываются в стек
	Queue(const ValueType* valueArray, std::size_t arraySize,
          QueueContainer container = QueueContainer::Vector);

	Queue(const Queue& copyQueue);
	Queue& operator=(const Queue& copyQueue);

	// Здесь как обычно
	Queue(Queue&& moveQueue) noexcept;
	Queue& operator=(Queue&& moveQueue) noexcept;

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
    QueueContainer _containerType;
};

