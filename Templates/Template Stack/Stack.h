#pragma once
#include "ListStack.h"
#include "VectorStack.h"
#include "StackImplementation.h"
#include <stdexcept>
#include <cstdlib>
#include <iostream>
using namespace std;

enum class StackContainer {
	Vector = 0,
	List,
};

template<typename ValueType>
class StackImplementation;

template<typename ValueType>
class Stack
{
public:
	// Большая пятерка
	Stack(StackContainer container = StackContainer::Vector);
	// элементы массива последовательно подкладываются в стек
	Stack(const ValueType* valueArray, const size_t arraySize,
		StackContainer container = StackContainer::Vector);

	explicit Stack(const Stack& copyStack);
	Stack& operator=(const Stack& copyStack);

	// Здесь как обычно
	Stack(Stack&& moveStack) noexcept;
	Stack& operator=(Stack&& moveStack) noexcept;

	~Stack();

	// добавление в хвост
	void push(const ValueType& value);
	// удаление с хвоста
	void pop();
	// посмотреть элемент в хвосте
	ValueType& top();
	const ValueType& top() const;
	// проверка на пустоту
	bool isEmpty() const;
	// размер 
	size_t size() const;
private:
	// указатель на имплементацию (уровень реализации)
	StackImplementation<ValueType>* _pimpl = nullptr;
	// тип контейнера, наверняка понадобится
	StackContainer _containerType;
};

template<typename ValueType>
Stack<ValueType>::Stack(StackContainer container)
	: _containerType(container)
{
	switch (container)
	{
	case StackContainer::List: {
		_pimpl = new ListStack<ValueType>();	// конкретизируйте под ваши конструкторы, если надо
		break;
	}
	case StackContainer::Vector: {
		_pimpl = new VectorStack<ValueType>();	// конкретизируйте под ваши конструкторы, если надо
		break;
	}
	default:
		throw std::runtime_error("Неизвестный тип контейнера");
	}
}

template<typename ValueType>
Stack<ValueType>::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container)
{
	_containerType = container;
	switch (container)
	{
	case StackContainer::List: {
		_pimpl = new ListStack<ValueType>();
		break;
	}
	case StackContainer::Vector: {
		_pimpl = new VectorStack<ValueType>();
		break;
	}
	default:
		throw std::runtime_error("Неизвестный тип контейнера");
	}

	for (size_t i = 0; i < arraySize; i++)
	{
		_pimpl->push(valueArray[i]);
	}
}

template<typename ValueType>
Stack<ValueType>::Stack(const Stack& copyStack)
{
	this->_containerType = copyStack._containerType;
	switch (_containerType)
	{
	case StackContainer::List: {
		_pimpl = new ListStack<ValueType>(*(static_cast<ListStack<ValueType>*>(copyStack._pimpl)));
		break;
	}
	case StackContainer::Vector: {
		_pimpl = new VectorStack<ValueType>(*(static_cast<VectorStack<ValueType>*>(copyStack._pimpl)));
		break;
	}
	default:
		throw std::runtime_error("Неизвестный тип контейнера");
	}
}

template<typename ValueType>
Stack<ValueType>::~Stack()
{
	delete _pimpl;		// композиция!
}

template<typename ValueType>
Stack<ValueType>& Stack<ValueType>::operator=(const Stack& copyStack)
{
	if (this == &copyStack)
	{
		return *this;
	}

	this->_containerType = copyStack._containerType;
	delete _pimpl;
	switch (_containerType)
	{
	case StackContainer::List: {
		_pimpl = new ListStack<ValueType>(*(static_cast<ListStack<ValueType>*>(copyStack._pimpl)));
		break;
	}
	case StackContainer::Vector: {
		_pimpl = new VectorStack<ValueType>(*(static_cast<VectorStack<ValueType>*>(copyStack._pimpl)));
		break;
	}
	default:
		throw std::runtime_error("Неизвестный тип контейнера");
	}

	return *this;
}

template<typename ValueType>
Stack<ValueType>::Stack(Stack&& moveStack) noexcept
{
	this->_containerType = moveStack._containerType;
	delete _pimpl;
	this->_pimpl = moveStack._pimpl;
	moveStack._pimpl = nullptr;

}

template<typename ValueType>
Stack<ValueType>& Stack<ValueType>::operator=(Stack&& moveStack) noexcept
{
	if (this == &moveStack)
	{
		return *this;
	}

	this->_containerType = moveStack._containerType;
	delete _pimpl;
	this->_pimpl = moveStack._pimpl;
	moveStack._pimpl = nullptr;

	return *this;
}

template<typename ValueType>
void Stack<ValueType>::push(const ValueType& value)
{
	// можно, т.к. push определен в интерфейсе
	_pimpl->push(value);
}

template<typename ValueType>
void Stack<ValueType>::pop()
{
	_pimpl->pop();
}

template<typename ValueType>
ValueType& Stack<ValueType>::top()
{
	return _pimpl->top();
}

template<typename ValueType>
const ValueType& Stack<ValueType>::top() const
{
	return _pimpl->top();
}

template<typename ValueType>
bool Stack<ValueType>::isEmpty() const
{
	return _pimpl->isEmpty();
}

template<typename ValueType>
size_t Stack<ValueType>::size() const
{
	return _pimpl->size();
}
