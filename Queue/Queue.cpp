#include "Queue.h"
#include "ListQueue.h"
#include "VectorQueue.h"
#include "DoubleListQueue.h"
#include "QueueImplementation.h"

#include <stdexcept>

Queue::Queue(StackContainer container)
	: _containerType(container)
{
	switch (container)
	{
	case StackContainer::List: {
		_pimpl = new ListQueue();
		break;
	}
	case StackContainer::Vector: {
		_pimpl = new VectorQueue();
		break;
	}
	case StackContainer::DoubleList: {
	    _pimpl = new DoubleListQueue();
	    break;
	}
	default:
		throw std::runtime_error("Неизвестный тип контейнера");
	}
}

Queue::Queue(const ValueType* valueArray, const size_t arraySize, StackContainer container) : Queue(container) {
    for(size_t i = 0; i < arraySize; i++) {
        _pimpl->enqueue(valueArray[i]);
    }
}

Queue::Queue(const Queue& copyStack) : Queue(copyStack._containerType) {
    size_t size = copyStack._pimpl->size();
    auto* arr = new ValueType[size];

    for(size_t i = 0; i < size; i++) {
        arr[i] = copyStack._pimpl->front();
        copyStack._pimpl->dequeue();
    }

    for(size_t i = 0; i < size; i++) {
        _pimpl->enqueue(arr[i]);
        copyStack._pimpl->enqueue(arr[i]);
    }

    delete[] arr;
}

Queue& Queue::operator=(const Queue& copyStack) {
    delete _pimpl;
    _containerType = copyStack._containerType;

    size_t size = copyStack._pimpl->size();
    auto* arr = new ValueType[size];

    for(size_t i = 0; i < size; i++) {
        arr[i] = copyStack._pimpl->front();
        copyStack._pimpl->dequeue();
    }

    for(size_t i = 0; i < size; i++) {
        _pimpl->enqueue(arr[i]);
        copyStack._pimpl->enqueue(arr[i]);
    }

    delete[] arr;

    return *this;
}

Queue::Queue(Queue &&moveStack) noexcept {
    delete _pimpl;
    _pimpl = moveStack._pimpl;
    _containerType = moveStack._containerType;

    moveStack._pimpl = nullptr;
}

Queue &Queue::operator=(Queue &&moveStack) noexcept {
    delete _pimpl;
    _pimpl = moveStack._pimpl;
    _containerType = moveStack._containerType;

    moveStack._pimpl = nullptr;

    return *this;
}

Queue::~Queue()
{
	delete _pimpl;		// композиция!
}

void Queue::enqueue(const ValueType& value)
{
	// можно, т.к. push определен в интерфейсе
	_pimpl->enqueue(value);
}

void Queue::dequeue()
{
	_pimpl->dequeue();
}

const ValueType& Queue::front() const
{
	return _pimpl->front();
}

bool Queue::isEmpty() const
{
	return _pimpl->isEmpty();
}

size_t Queue::size() const
{
	return _pimpl->isEmpty();
}
