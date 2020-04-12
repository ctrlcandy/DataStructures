#include <cmath>
#include <stdexcept>

#include "MyVector.h"

void MyVector::deleteData() {
    if (_data != nullptr) {
        auto* bufData = new ValueType[_capacity];
        std::copy(bufData, bufData + _capacity, _data);
        delete[] bufData;
    }
}

void MyVector::resize() {
    deleteData();

    switch (_strategy) {
        case (ResizeStrategy::Multiplicative):
            if (_size == 0)
                _capacity = 1;
            else
                _capacity = std::ceil(_coef * _capacity);
            break;

        case (ResizeStrategy::Additive):
            _capacity += std::ceil(_coef);
            break;

        default:
            throw std::invalid_argument("Incorrect ResizeStrategy");
    }

    _data = new ValueType[_capacity];
}

MyVector::MyVector(size_t size, ResizeStrategy strategy, float coef):
    _size(size), _capacity (size), _strategy (strategy), _coef (coef)
{
    resize();
}

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy strategy, float coef):
    _size(size), _capacity (size), _strategy (strategy), _coef (coef)
{
    resize();
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = value;
    }
}

MyVector::MyVector(const MyVector &copy):
    _size(copy._size), _capacity (copy._capacity), _strategy (copy._strategy), _coef (copy._coef)
{
    _data = new ValueType[_capacity];

    for (size_t i = 0; i < copy._capacity; ++i) {
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


    deleteData();
    _data = new ValueType[copy._capacity];
    for (size_t i = 0; i < copy._size; ++i) {
        _data[i] = copy._data[i];
    }

    return *this;
}

MyVector::~MyVector() {
    delete[] _data;
    _data = nullptr;
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

void MyVector::checkLoadFactorAndCopy(size_t numToCopy) {
    if (loadFactor() > 1 || loadFactor() <=  1/(_coef *_coef)) {
        MyVector bufVector(*this);
        checkLoadFactorAndResize();
        bufVector._size = numToCopy;
        for (size_t i = 0; i < bufVector._size; ++i)
            _data[i] = bufVector._data[i];
    }
}

void MyVector::checkLoadFactorAndResize() {
    if (loadFactor() > 1) {
        resize();
    }
    else if (loadFactor() <=  1/(_coef *_coef)) {
        if (_strategy == ResizeStrategy::Multiplicative) {
            float coef = _coef;
            _coef = 1 / _coef;
            resize();
            _coef = coef;
        }
        else if (_strategy == ResizeStrategy::Additive){
            _capacity = _size;
            resize();
        }
    }
}

ValueType &MyVector::operator[](const size_t i) const {
    return _data[i];
}

void MyVector::pushBack(const ValueType &value) {
    ++_size;
    checkLoadFactorAndCopy(_size - 1);
    _data[_size - 1] = value;
}

void MyVector::insert(const size_t idx, const ValueType &value) {
    if (idx > _size)
        throw std::length_error("Incorrect index");
    else if (idx == _size) {
        popBack();
        return;
    }

    ++_size;
    checkLoadFactorAndCopy(_size - 1);

    for (size_t i = _size - 1; i > idx; --i) {
        _data[i] = _data [i - 1];
    }
    _data[idx] = value;
}

void MyVector::insert(const size_t idx, const MyVector &value) {
    if (idx > _size)
        throw std::length_error("Incorrect index");
    else if (idx == _size) {
        popBack();
        return;
    }

    _size += value._size;
    checkLoadFactorAndCopy(_size - value._size);

    for (size_t i = _size; i > idx; --i) {
        _data[i] = _data[i - value._size];
    }

    for (size_t i = idx; i < idx + value._size; ++i) {
        _data[i] = value._data[value._size - idx];
    }
}

void MyVector::popBack() {
    if (_size == 0)
        throw std::length_error("MyVector is empty");

    --_size;
    checkLoadFactorAndCopy(_size);
}

void MyVector::erase(const size_t idx) {
    if (_size == 0)
        throw std::length_error("MyVector is empty");
    else if (idx > _size - 1)
        throw std::length_error("Incorrect index");
    else if (idx == _size - 1)
        popBack();

    --_size;
    checkLoadFactorAndCopy(_size + 1);

    for (size_t i = idx; i < _size + 1; ++i)
        _data[i] = _data [i + 1];
}

void MyVector::erase(const size_t idx, const size_t len) {
    if (_size == 0)
        throw std::length_error("MyVector is empty");
    else if (idx > _size - 1)
        throw std::length_error("Incorrect index");

    _size -= len;
    checkLoadFactorAndCopy(_size + len);

    for (size_t i = idx; i < _size + len; ++i)
        _data[i] = _data [i + len];
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
    deleteData();
    _capacity = capacity;
    _data = new ValueType[capacity]();

    for (size_t i = 0; i < _size; ++i)
        _data[i] = bufVector._data [i];
}

void MyVector::resize(const size_t size, const ValueType value) {
    MyVector bufVector(*this);
    _size = size;

    checkLoadFactorAndCopy(_size);
    if (_size > bufVector._size) {
        for (size_t i = bufVector._size; i < _size; ++i)
            _data[i] = value;
    }
}

void MyVector::clear() {
    for (size_t i = 0; i < _size; ++i)
        _data[i] = 0;

    _size = 0;
}

MyVector MyVector::sortedSquares(const MyVector &vector, SortedStrategy strategy) {
    MyVector res(vector);

    size_t left = 0;
    size_t right = vector._size - 1;

    int currentLeft =  std::pow(vector._data[0], 2);
    int currentRight =  std::pow(vector._data[res._size - 1], 2);

    switch (strategy) {
        case (SortedStrategy::Increase):
            for (int i = vector._size - 1; i >=  0; --i) {
                if (currentLeft > currentRight) {
                    res._data[i] = currentLeft;
                    ++left;
                    currentLeft = std::pow(vector._data[left], 2);
                }
                else {
                    res._data[i] = currentRight;
                    --right;
                    currentRight = std::pow(vector._data[right], 2);
                }
            }
            break;
        case (SortedStrategy::Decrease):
            for (int i = 0; i < vector._size; ++i) {
                if (currentLeft > currentRight) {
                    res._data[i] = currentLeft;
                    ++left;
                    currentLeft = std::pow(vector._data[left], 2);
                }
                else {
                    res._data[i] = currentRight;
                    --right;
                    currentRight = std::pow(vector._data[right], 2);
                }
            }
            break;
        default:
            throw std::invalid_argument("Incorrect SortedStrategy");
    }
    return res;
}
