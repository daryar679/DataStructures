#pragma once

#include "StackImplementation.h"
#include "LinkedList.h"
#include <cstdlib>

template<typename ValueType>
class ListStack : public StackImplementation<ValueType>, public LinkedList<ValueType>
{
	public:
	ListStack() {};
	ListStack(const ListStack& copyList);
	void push(const ValueType& value) override;
	// удаление с хвоста
	void pop()override;
	// посмотреть элемент в хвосте
	ValueType& top()override;
	const ValueType& top() const override;
	// проверка на пустоту
	bool isEmpty() const override;
	// размер 
	size_t size() const override;
	// виртуальный деструктор
	~ListStack()override {};
};

template<typename ValueType>
ListStack<ValueType>::ListStack(const ListStack& copyList) :LinkedList<ValueType>(copyList)
{
}

template<typename ValueType>
void ListStack<ValueType>::push(const ValueType& value)
{
	this->pushFront(value);
}

template<typename ValueType>
void ListStack<ValueType>::pop()
{
	this->removeFront();
}

template<typename ValueType>
ValueType& ListStack<ValueType>::top()
{
	return LinkedList<ValueType>::getNode(0)->value;
}

template<typename ValueType>
const ValueType& ListStack<ValueType>::top() const
{
	return LinkedList<ValueType>::getNode(0)->value;
}

template<typename ValueType>
bool ListStack<ValueType>::isEmpty() const
{
	if (size() == 0)
		return true;
	else
		return false;
}

template<typename ValueType>
size_t ListStack<ValueType>::size() const
{
	return LinkedList<ValueType>::size();
}
