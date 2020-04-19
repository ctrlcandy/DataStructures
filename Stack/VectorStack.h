#pragma once
#include "StackImplementation.h"
#include "MyVector.h" // меняете на include вашего вектора

// вариант с использованием ранее написанного вектора и множественного наследования
// если бы вектор не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
class VectorStack : public StackImplementation, public MyVector {
public:
    VectorStack();
    VectorStack(const VectorStack& copyVector);

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
    ~VectorStack() override {};
};

