#include "Queue.h"
#include "ListQueue.h"
#include "VectorQueue.h"
#include "DoubleListQueue.h"
#include "QueueImplementation.h"

#include <stdexcept>

Queue::Queue(QueueContainer container)
	: _containerType(container)
{
	switch (container)
	{
	case QueueContainer::List: {
		_pimpl = new ListQueue();
		break;
	}
	case QueueContainer::Vector: {
		_pimpl = new VectorQueue();
		break;
	}
	case QueueContainer::DoubleList: {
	    _pimpl = new DoubleListQueue();
	    break;
	}
	default:
		throw std::runtime_error("Неизвестный тип контейнера");
	}
}

Queue::Queue(const ValueType* valueArray, const size_t arraySize, QueueContainer container) : Queue(container) {
    for(size_t i = 0; i < arraySize; i++) {
        _pimpl->enqueue(valueArray[i]);
    }
}

Queue::Queue(const Queue& copyQueue) : Queue(copyQueue._containerType) {
    switch (_containerType)
    {
        case QueueContainer::List: {
            auto list(dynamic_cast<LinkedList*>(copyQueue._pimpl));
            for(size_t i = 0; i < list->size(); i++) {
                _pimpl->enqueue(list->operator[](i));
            }
            break;
        }
        case QueueContainer::Vector: {
            auto vector(dynamic_cast<MyVector*>(copyQueue._pimpl));
            for(size_t i = 0; i < vector->size(); i++) {
                _pimpl->enqueue(vector->operator[](i));
            }
            break;
        }
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }
}

Queue& Queue::operator=(const Queue& copyQueue) {
    if (this == &copyQueue) {
        return *this;
    }

    delete _pimpl;
    _containerType = copyQueue._containerType;

    switch (_containerType)
    {
        case QueueContainer::List: {
            auto list(dynamic_cast<LinkedList*>(copyQueue._pimpl));
            for(size_t i = 0; i < list->size(); i++) {
                _pimpl->enqueue(list->operator[](i));
            }
            break;
        }
        case QueueContainer::Vector: {
            auto vector(dynamic_cast<MyVector*>(copyQueue._pimpl));
            for(size_t i = 0; i < vector->size(); i++) {
                _pimpl->enqueue(vector->operator[](i));
            }
            break;
        }
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }

    return *this;
}

Queue::Queue(Queue &&moveQueue) noexcept {
    delete _pimpl;
    _pimpl = moveQueue._pimpl;
    _containerType = moveQueue._containerType;

    moveQueue._pimpl = nullptr;
}

Queue &Queue::operator=(Queue &&moveQueue) noexcept {
    delete _pimpl;
    _pimpl = moveQueue._pimpl;
    _containerType = moveQueue._containerType;

    moveQueue._pimpl = nullptr;

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
	return _pimpl->size();
}
