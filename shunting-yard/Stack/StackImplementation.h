#pragma once

// приходится тянуть ValueType во все места,
// наглядная демонстрация того, почему с шаблонами было бы легче.
// Ждем, когда дойдете до этого на МиСП.
#include <cstddef>
#include "../Tokens/AbstractToken.h"

using ValueType = AbstractToken;

// интерфейс для конкретных реализаций контейнера для стека
class StackImplementation {
public:
	// добавление в хвост
	virtual void push(const ValueType& value) = 0;
	// удаление с хвоста
	virtual void pop() = 0;
	// посмотреть элемент в хвосте
	virtual const ValueType& top() const = 0;
	// проверка на пустоту
	virtual bool isEmpty() const = 0;
	// размер 
	virtual std::size_t size() const = 0;
	// виртуальный деструктор
	virtual ~StackImplementation() {};
};
