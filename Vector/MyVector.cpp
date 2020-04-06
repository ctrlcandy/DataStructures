#include <cmath>
#include <stdexcept>

#include "MyVector.h"

void MyVector::resize(size_t size, ResizeStrategy strategy, float coef)
{
    _size = size;
    if(strategy == ResizeStrategy::Multiplicative) {
        if (_size == 0)
            _capacity = 1;
        else
            _capacity = std::ceil(coef * size);
    }
    else if(strategy == ResizeStrategy::Additive) {
        _capacity += std::ceil(coef);
    }
    else {
        throw std::invalid_argument("Incorrect ResizeStrategy");
    }

    _strategy = strategy;
    _coef = coef;
    _data = new ValueType[_capacity]();
}

MyVector::MyVector(size_t size, ResizeStrategy strategy, float coef)
{
    resize(size, strategy, coef);
}

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy strategy, float coef) {
    resize(size, strategy, coef);

    for (int i = 0; i < _capacity; ++i) {
        _data[i] = value;
    }
}

MyVector::MyVector(const MyVector &copy) {
    _size = copy._size;
    _capacity = copy._capacity;

    _data = new ValueType[_capacity];
    for (int i = 0; i < _size; ++i) {
        _data[i] = copy._data[i];
    }
}

MyVector& MyVector::operator=(const MyVector &copy) {
    _size = copy._size;
    _capacity = copy._capacity;

    _data = new ValueType[_capacity];
    for (int i = 0; i < _size; ++i) {
        _data[i] = copy._data[i];
    }
}

MyVector::~MyVector() {
    delete[] _data;
    _size = 0;
    _capacity = 0;
}

MyVector::MyVector(MyVector &&moveVector) noexcept {
    _size = moveVector._size;
    _capacity = moveVector._capacity;
    _data = moveVector._data;

    moveVector._size = 0;
    moveVector._capacity = 0;
    moveVector._data = nullptr;
}

MyVector& MyVector::operator=(MyVector &&moveVector) noexcept {

    _size = moveVector._size;
    _capacity = moveVector._capacity;
    _data = moveVector._data;

    moveVector._size = 0;
    moveVector._capacity = 0;
    moveVector._data = nullptr;

    return *this;
}

size_t MyVector::capacity() const {
    return _capacity;
}

size_t MyVector::size() const {
    return _size;
}

float MyVector::loadFactor() {
    return (float)_size/_capacity;
}

ValueType &MyVector::operator[](const size_t i) const {
    return _data[i];
}

void MyVector::pushBack(const ValueType &value) {
    if (_size + 1 > _capacity)
        resize(_size, _strategy, _coef);

    _data[_size] = value;
    ++_size;
}

void MyVector::insert(const size_t idx, const ValueType &value) {
    if (idx > _size - 1)
        throw std::invalid_argument("Incorrect index");
    else if (idx == _size)
        popBack();
    else if (_size + 1 > _capacity) {
        MyVector* bufVector = new MyVector(*this);
        resize(_size, _strategy, _coef);

        for (int i = 0; i < bufVector->_size; ++i)
            _data[i] = bufVector->_data [i];
        }

    ++_size;
    for (int i = idx + 1; i < _size + 1; ++i) {
        _data[i] = _data [i - 1];
    }
    _data[idx] = value;
}

void MyVector::insert(const size_t i, const MyVector &value) {

}

void MyVector::popBack() {

}

void MyVector::erase(const size_t i) {

}

void MyVector::erase(const size_t i, const size_t len) {

}

long long int MyVector::find(const ValueType &value, bool isBegin) const {
    return 0;
}

void MyVector::reserve(const size_t capacity) {

}

void MyVector::resize(const size_t size, const ValueType) {

}

void MyVector::clear() {

}

