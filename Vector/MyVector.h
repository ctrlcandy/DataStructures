#pragma once

#include <cstddef>

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
using ValueType = double;

class MyVector
{
public:

    class MyIterator {

    public:
        MyIterator(ValueType* p) : ptr(p) {};
        MyIterator(const MyIterator& it) : ptr(it.ptr) {};

        MyIterator operator+ (int n) { return MyIterator(ptr + n); }
        MyIterator operator- (int n) { return MyIterator(ptr - n); }

        MyIterator operator++ () { return ++ptr; }
        MyIterator operator-- () { return --ptr; }

        MyIterator operator++ (int) { return ptr++; }
        MyIterator operator-- (int) { return ptr--; }


        bool operator!=(const MyIterator& it) const { return ptr != it.ptr; }
        bool operator==(const MyIterator& it ) const { return ptr == it.ptr; }

        ValueType& operator*() { return *ptr; }
		ValueType& operator->() { return *ptr; }

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
	ValueType& operator[](const size_t i) const;

	// добавить в конец,
	// должен работать за amort(O(1))
	void pushBack(const ValueType& value);
	// вставить,
	// должен работать за O(n)
	void insert(const size_t i, const ValueType& value);	// версия для одного значения
	void insert(const size_t i, const MyVector& value);		// версия для вектора

	// удалить с конца,
	// должен работать за amort(O(1))
	void popBack();
	// удалить
	// должен работать за O(n)
	void erase(const size_t i);
	void erase(const size_t i, const size_t len);			// удалить len элементов начиная с i

	// найти элемент,
	// должен работать за O(n)
	// если isBegin == true, найти индекс первого элемента, равного value, иначе последнего
	// если искомого элемента нет, вернуть -1
	long long int find(const ValueType& value, bool isBegin = true) const;	

	// зарезервировать память (принудительно задать capacity)
	void reserve(const size_t capacity);

	// изменить размер
	// если новый размер больше текущего, то новые элементы забиваются дефолтными значениями
	// если меньше - обрезаем вектор
	void resize(const size_t size, const ValueType = 0.0);

	// очистка вектора, без изменения capacity
	void clear();

	// итераторы
    using iterator = MyIterator;
    using const_iterator = MyIterator;

    iterator begin() { return MyIterator(_data); };
    iterator end() { return MyIterator(_data + _size); };

    const_iterator begin() const { return MyIterator(_data); };
    const_iterator end() const { return MyIterator(_data + _size); };

    static MyVector sortedSquares(const MyVector& vector, SortedStrategy = SortedStrategy::Increase);

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

