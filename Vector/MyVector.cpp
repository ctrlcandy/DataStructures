#include <cmath>
#include <stdexcept>
#include <cstring>

#include "MyVector.h"

void MyVector::resize() {
    switch (_strategy) {
        case (ResizeStrategy::Multiplicative) :
            if (_size == 0)
                _capacity = 1;
            else
                _capacity = std::ceil(_coef * _capacity);
            break;

        case (ResizeStrategy::Additive) :
            _capacity += std::ceil(_coef);
            break;

        default:
            throw std::invalid_argument("Incorrect ResizeStrategy");
    }

    _data = new ValueType[_capacity];
    /*if (_data != nullptr) {
        ValueType *tmp_data = new ValueType[sizeof(_data)/sizeof(_data[0])];
        memcpy(tmp_data, _data, sizeof(ValueType) * (sizeof(_data)/sizeof(_data[0])));
        delete[] tmp_data;
        _data = new ValueType[_capacity];
    }
    else
    {
        _data = new ValueType[_capacity];
    } */
}

MyVector::MyVector(size_t size, ResizeStrategy strategy, float coef) {
    _size = size;
    _capacity = size;
    _strategy = strategy;
    _coef = coef;

    resize();
}

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy strategy, float coef) {
    _size = size;
    _capacity = size;
    _strategy = strategy;
    _coef = coef;

    resize();

    for (size_t i = 0; i < _size; ++i) {
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


    //delete[] _data;

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

void MyVector::resizeAndCopy() {
    if (loadFactor() > 1) {
        MyVector bufVector(*this);
        resize();
        for (size_t i = 0; i < bufVector._size; ++i)
            _data[i] = bufVector._data[i];
    }
    else if (loadFactor() <=  1/(_coef *_coef)) {
        MyVector bufVector(*this);

        _coef = 1 / _coef * _capacity;
        resize();
        _coef = bufVector._coef;

        for (size_t i = 0; i < _size; ++i)
            _data[i] = bufVector._data [i];
    }
}

ValueType &MyVector::operator[](const size_t i) const {
    return _data[i];
}

void MyVector::pushBack(const ValueType &value) {
    ++_size;
    resizeAndCopy();
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
    resizeAndCopy();

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
    resizeAndCopy();

    for (size_t i = _size; i > idx; --i) {
        _data[i] = _data[i - value._size];
    }

    int j = 0;
    for (size_t i = idx; i < idx + value._size; ++i) {
        _data[i] = value._data[j];
        j++;
    }
}

void MyVector::popBack() {
    if (_size == 0)
        throw std::length_error("MyVector is empty");

    --_size;
    resizeAndCopy();
}

void MyVector::erase(const size_t idx) {
    if (_size == 0)
        throw std::length_error("MyVector is empty");
    else if (idx > _size - 1)
        throw std::length_error("Incorrect index");
    else if (idx == _size - 1)
        popBack();

    --_size;
    resizeAndCopy();

    for (size_t i = idx; i < _size + 1; ++i)
        _data[i] = _data [i + 1];
}

void MyVector::erase(const size_t idx, const size_t len) {
    if (_size == 0)
        throw std::length_error("MyVector is empty");
    else if (idx > _size - 1)
        throw std::length_error("Incorrect index");

    --_size;
    resizeAndCopy();

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
    _size = size;
    resize();

    if (_size > bufVector._size) {
        for (size_t i = 0; i < bufVector._size; ++i)
            _data[i] = bufVector._data [i];

        for (size_t i = bufVector._size; i < _size; ++i)
            _data[i] = value;
    }
    else {
        for (size_t i = 0; i < _size; ++i)
            _data[i] = bufVector._data[i];
    }

}

void MyVector::clear() {
    //for (size_t i = 0; i < _size; ++i)
    // _data[i] = 0;

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
