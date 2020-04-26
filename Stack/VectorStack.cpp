#include "VectorStack.h"
#include "Vector.h"

VectorStack::VectorStack(const VectorStack& copy):MyVector(copy)
{
}

void VectorStack::push(const ValueType& value)
{
	this->pushBack(value);
}

void VectorStack::pop()
{
	this->popBack();
}

ValueType& VectorStack::top()
{
	return operator[](size() - 1);
}

const ValueType& VectorStack::top() const
{
	return operator[](size() - 1);
}

bool VectorStack::isEmpty() const
{
	if (size() == 0)
		return true;
	else
		return false;
}

size_t VectorStack::size() const
{
	return MyVector::size();
}
