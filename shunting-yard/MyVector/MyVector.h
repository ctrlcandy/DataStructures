#pragma once

#include <cstddef>
#include "../Tokens/Token.h"

// стратегия изменения capacity
enum class ResizeStrategy {
	Additive,
	Multiplicative
};

enum class SortedStrategy {
    Increase,
    Decrease
};

// тип значений в векторе
// потом будет заменен на шаблон
using ValueType = Token;

class MyVector
{
public:

    class Iterator {

    public:
        Iterator(ValueType* p) : ptr(p) {};
        Iterator(const Iterator& it) : ptr(it.ptr) {};

        Iterator operator+ (int n) { return Iterator(ptr + n); }
        Iterator operator- (int n) { return Iterator(ptr - n); }

        Iterator operator++ () { return ++ptr; }
        Iterator operator-- () { return --ptr; }

        Iterator operator++ (int) { return ptr++; }
        Iterator operator-- (int) { return ptr--; }


        bool operator!=(const Iterator& it) const { return ptr != it.ptr; }
        bool operator==(const Iterator& it ) const { return ptr == it.ptr; }

        ValueType& operator*() const { return *ptr; }
        ValueType* operator->() const { return ptr; }

    protected:
        ValueType* ptr;
    };

	class ConstIterator : public Iterator {

	public:
        ConstIterator(ValueType *p) : Iterator(p), ptr(p) {};
        ConstIterator(const ConstIterator& it) : Iterator(it), ptr(it.ptr) {};

        const ValueType& operator*() const { return *ptr; }
        const ValueType* operator->() const { return ptr; }

	private:
		ValueType* ptr;
	};

	explicit MyVector(size_t size = 0, ResizeStrategy = ResizeStrategy::Multiplicative, float coef = 1.5f);
	MyVector(size_t size, ValueType value, ResizeStrategy = ResizeStrategy::Multiplicative, float coef = 1.5f);
	
	MyVector(const MyVector& copy);
	MyVector& operator=(const MyVector& copy);

	~MyVector();

    MyVector(MyVector&& moveVector) noexcept;
    MyVector& operator=(MyVector&& moveVector) noexcept;

	size_t capacity() const;
	size_t size() const;
	float loadFactor();

	// доступ к элементу, 
	// должен работать за O(1)
	ValueType& operator[](size_t i) const;

	// добавить в конец,
	// должен работать за amort(O(1))
	void pushBack(const ValueType& value);
	// вставить,
	// должен работать за O(n)
	void insert(size_t i, const ValueType& value);	// версия для одного значения
	void insert(size_t i, const MyVector& value);	// версия для вектора

	// удалить с конца,
	// должен работать за amort(O(1))
	void popBack();
	// удалить
	// должен работать за O(n)
	void erase(size_t i);
	void erase(size_t i, size_t len);			// удалить len элементов начиная с i

	// найти элемент,
	// должен работать за O(n)
	// если isBegin == true, найти индекс первого элемента, равного value, иначе последнего
	// если искомого элемента нет, вернуть -1
	long long int find(const ValueType& value, bool isBegin = true) const;	

	// зарезервировать память (принудительно задать capacity)
	void reserve(size_t capacity);

	// изменить размер
	// если новый размер больше текущего, то новые элементы забиваются дефолтными значениями
	// если меньше - обрезаем вектор
	void resize(size_t size, ValueType);

	// очистка вектора, без изменения capacity
	void clear();

	// итераторы
    using iterator = Iterator;
    using const_iterator = ConstIterator;

	iterator begin() { return Iterator(_data); };
    iterator end() { return Iterator(_data + _size); };

	const_iterator cbegin() const { return ConstIterator(_data); };
    const_iterator cend() const { return ConstIterator(_data + _size); };

    //static MyVector sortedSquares(const MyVector& vector, SortedStrategy = SortedStrategy::Increase);

private:
	ValueType* _data;
	size_t _size;
	size_t _capacity;

    ResizeStrategy _strategy;
    float _coef;

    void deleteData();
	void resizeVector(size_t capacity, float coef);
	void checkLoadFactorAndCopy(size_t numToCopy);
    void checkLoadFactorAndResize();
};
