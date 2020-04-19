#pragma once

#include "QueueImplementation.h"
#include "DoubleLinkedList.h"// меняете на include вашего листа

// вариант с использованием ранее написанного списка и множественного наследования
// если бы список не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
class DoubleListQueue : public QueueImplementation, public DoubleLinkedList
{
public:
    DoubleListQueue() {};
    DoubleListQueue(const DoubleListQueue& copyList);

    // добавление в хвост
    void enqueue(const ValueType& value) override;

    // удаление с хвоста
    void dequeue() override;

    // посмотреть элемент в хвосте
    const ValueType &front() const override;

    // проверка на пустоту
    bool isEmpty() const override;

    // размер
    std::size_t size() const override;

    // виртуальный деструктор
    ~DoubleListQueue() override {};
};