#pragma once

// приходится тянуть ValueType во все места,
// наглядная демонстрация того, почему с шаблонами было бы легче.
// Ждем, когда дойдете до этого на МиСП.
#include <cstddef>

using ValueType = double;

// интерфейс для конкретных реализаций контейнера для стека
class QueueImplementation {
public:
	// поставить элемент в очередь
	virtual void enqueue(const ValueType& value) = 0;
	// достать первый элемент из очереди
	virtual void dequeue() = 0;
	// посмотреть элемент в голове очереди
	virtual const ValueType& front() const = 0;
	// проверка на пустоту
	virtual bool isEmpty() const = 0;
	// размер 
	virtual std::size_t size() const = 0;
	// виртуальный деструктор
	virtual ~QueueImplementation() {};
};
