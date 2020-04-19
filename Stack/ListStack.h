#pragma once

#include "StackImplementation.h"
#include "LinkedList.h"// меняете на include вашего листа

// вариант с использованием ранее написанного списка и множественного наследования
// если бы список не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
class ListStack : public StackImplementation, public LinkedList
{
public:
    ListStack();
    ListStack(const ListStack& copyList);

    // добавление в хвост
    void push(const ValueType& value) override;

    // удаление с хвоста
    void pop() override;

    // посмотреть элемент в хвосте
    const ValueType &top() const override;

    // проверка на пустоту
    bool isEmpty() const override;

    // размер
    std::size_t size() const override;

    // виртуальный деструктор
    ~ListStack() override {};
};

