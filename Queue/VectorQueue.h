#pragma once
#include "QueueImplementation.h"
#include "MyVector.h" // меняете на include вашего вектора
#include "ListQueue.h"
#include <iostream>
using std::cout;
using std::endl;

// вариант с использованием ранее написанного вектора и множественного наследования
// если бы вектор не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
class VectorQueue : public QueueImplementation, public MyVector {
public:
    VectorQueue() : _backIndex(0) {};

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
    ~VectorQueue() override {};

private:
    size_t _backIndex;
};

