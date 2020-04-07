#include <cmath>
#include <stdexcept>

#include "MyVector.h"

void MyVector::resize(size_t size, ResizeStrategy strategy, float coef) {
    if(strategy == ResizeStrategy::Multiplicative) {
        if (_size == 0)
            _capacity = 1;
        else
            _capacity = std::ceil(coef * _capacity);
    }
    else if(strategy == ResizeStrategy::Additive) {
        _capacity += std::ceil(coef);
    }
    else {
        throw std::invalid_argument("Incorrect ResizeStrategy");
    }

    _data = new ValueType[_capacity]();
}

MyVector::MyVector(size_t size, ResizeStrategy strategy, float coef) {
    _size = size;
    _capacity = size;
    _strategy = strategy;
    _coef = coef;
    resize(size, strategy, coef);
}

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy strategy, float coef) {
    _size = size;
    _capacity = size;
    _strategy = strategy;
    _coef = coef;
    resize(size, strategy, coef);

    for (size_t i = 0; i < _capacity; ++i) {
        _data[i] = value;
    }
}

MyVector::MyVector(const MyVector &copy) {
    _size = copy._size;
    _capacity = copy._capacity;
    _strategy = copy._strategy;
    _coef = copy._coef;

    _data = new ValueType[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = copy._data[i];
    }
}

MyVector& MyVector::operator=(const MyVector &copy) {
    if(this == &copy)
        return *this;

    _size = copy._size;
    _capacity = copy._capacity;
    _strategy = copy._strategy;
    _coef = copy._coef;

    delete _data;
    _data = new ValueType[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = copy._data[i];
    }

    return *this;
}

MyVector::~MyVector() {
    delete[] _data;
}

MyVector::MyVector(MyVector &&moveVector) noexcept {
    _size = moveVector._size;
    _capacity = moveVector._capacity;
    _data = moveVector._data;
    _strategy = moveVector._strategy;
    _coef = moveVector._coef;

    moveVector._data = nullptr;
}

MyVector& MyVector::operator=(MyVector &&moveVector) noexcept {

    _size = moveVector._size;
    _capacity = moveVector._capacity;
    _data = moveVector._data;
    _strategy = moveVector._strategy;
    _coef = moveVector._coef;

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
    if (_size + 1 > _capacity) {
        MyVector bufVector(*this);
        resize(_size + 1, _strategy, _coef);

        for (size_t i = 0; i < bufVector._size; ++i)
            _data[i] = bufVector._data [i];
    }

    _data[_size] = value;
    ++_size;
}

void MyVector::insert(const size_t idx, const ValueType &value) {
    if (idx >= _size - 1)
        throw std::length_error("Incorrect index");
    //Я не уверена, что это корректно, поскольку
    //это выход за границы массива
    //(тогда знак в проверке выше меняется на >)
    /*else if (idx == _size)
        popBack();*/
    else if (_size + 1 > _capacity) {
        MyVector bufVector(*this);
        resize(_size + 1, _strategy, _coef);

        for (size_t i = 0; i < bufVector._size; ++i)
            _data[i] = bufVector._data [i];
        }

    ++_size;
    for (size_t i = _size - 1; i > idx; --i) {
        _data[i] = _data [i - 1];
    }
    _data[idx] = value;
}

void MyVector::insert(const size_t idx, const MyVector &value) {
    if (idx >= _size)
        throw std::length_error("Incorrect index");
    //Я не уверена, что это корректно, поскольку
    //это выход за границы массива
    //(тогда знак в проверке выше меняется на >)
    /*else if (idx == _size)
        popBack();*/
    else if (_size + value._size > _capacity) {
        MyVector bufVector(*this);
        resize(_size + value._size, _strategy, _coef);

        for (size_t i = 0; i < bufVector._size; ++i)
            _data[i] = bufVector._data [i];
    }

    _size += value._size;
    for (size_t i = _size - 1; i > idx; --i) {
        _data[i] = _data [i - value._size];
    }
    for (size_t i = idx; i < value._size; ++i) {
        _data[i] = value._data[i];
    }
}

void MyVector::popBack() {
    if (_size == 0)
        throw std::length_error("MyVector is empty");

    else if (loadFactor() <=  1/(_coef *_coef)) {
        MyVector bufVector(*this);
        resize(_size, _strategy, 1 / _coef * _capacity);

        for (size_t i = 0; i < _size; ++i)
            _data[i] = bufVector._data [i];
    }

    _data[_size - 1].~ValueType();
    --_size;
}

void MyVector::erase(const size_t idx) {
    if (_size == 0)
        throw std::length_error("MyVector is empty");
    else if (idx > _size - 1)
        throw std::length_error("Incorrect index");
    else if (idx == _size - 1)
        popBack();

    else if (loadFactor() <=  1/(_coef *_coef)) {
        MyVector bufVector(*this);
        resize(_size, _strategy, 1 / _coef * _capacity);

        for (size_t i = 0; i < _size; ++i)
            _data[i] = bufVector._data [i];
    }

    _data[idx].~ValueType();
    --_size;
    for (size_t i = idx; i < _size; ++i)
        _data[i] = _data [i + 1];
}

void MyVector::erase(const size_t idx, const size_t len) {
    if (_size == 0)
        throw std::length_error("MyVector is empty");
    else if (idx > _size - 1)
        throw std::length_error("Incorrect index");

    else if (loadFactor() <=  1/(_coef *_coef)) {
        MyVector bufVector(*this);
        resize(_size, _strategy, 1 / _coef * _capacity);

        for (size_t i = 0; i < _size; ++i)
            _data[i] = bufVector._data [i];
    }

    _data[idx].~ValueType();
    --_size;
    for (size_t i = idx; i < _size; ++i)
        _data[i] = _data [i + 1];
}

long long int MyVector::find(const ValueType &value, bool isBegin) const {
    if (isBegin) {
        for (size_t i = 0; i < _size; ++i)
            if (_data[i] == value)
                return  _data[i];
    }
    else {
        for (size_t i = _size - 1; i > 0; --i)
            if (_data[i] == value)
                return  _data[i];
    }
    return -1;
}

void MyVector::reserve(const size_t capacity) {
    MyVector bufVector(*this);
    _data = new ValueType[capacity]();
    _capacity = capacity;

    for (size_t i = 0; i < _size; ++i)
        _data[i] = bufVector._data [i];
}

void MyVector::resize(const size_t size, const ValueType value) {
    MyVector bufVector(*this);
    resize(_size, _strategy, _coef);

    for (size_t i = 0; i < _size; ++i)
        _data[i] = bufVector._data [i];
}

void MyVector::clear() {
    for (size_t i = 0; i < _size; ++i)
        _data[i].~ValueType();

    _size = 0;
}

MyVector MyVector::sortedSquares(const MyVector &vec, SortedStrategy strategy) {
    return MyVector();
}
