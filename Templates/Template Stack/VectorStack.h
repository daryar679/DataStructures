#pragma once
#include "StackImplementation.h"
#include "MyVector.h"
#include <cstdlib>

template<typename ValueType>

class VectorStack : public StackImplementation<ValueType>, public MyVector<ValueType>
{
	public:
	VectorStack() {};
	VectorStack(const VectorStack& copy);
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
	~VectorStack() override {};
};

template<typename ValueType>
VectorStack<ValueType>::VectorStack(const VectorStack& copy) :MyVector<ValueType>(copy)
{
}

template<typename ValueType>
void VectorStack<ValueType>::push(const ValueType& value)
{
	this->pushBack(value);
}

template<typename ValueType>
void VectorStack<ValueType>::pop()
{
	this->popBack();
}

template<typename ValueType>
ValueType& VectorStack<ValueType>::top()
{
	return MyVector<ValueType>::operator[](size() - 1);
}

template<typename ValueType>
const ValueType& VectorStack<ValueType>::top() const
{
	return MyVector<ValueType>::operator[](size() - 1);
}

template<typename ValueType>
bool VectorStack<ValueType>::isEmpty() const
{
	if (size() == 0)
		return true;
	else
		return false;
}

template<typename ValueType>
size_t VectorStack<ValueType>::size() const
{
	return MyVector<ValueType>::size();
}
