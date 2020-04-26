#include "ListStack.h"
#include "LinkedList.h"

ListStack::ListStack(const ListStack& copyList):LinkedList(copyList)
{
}

void ListStack::push(const ValueType& value)
{
	this->pushBack(value);
}

void ListStack::pop()
{
	this->removeBack();
}

ValueType& ListStack::top()
{
	return operator[](size() - 1);
}

const ValueType& ListStack::top() const
{
	return operator[](size() - 1);
}

bool ListStack::isEmpty() const
{
	if (size() == 0)
		return true;
	else
		return false;
}

size_t ListStack::size() const
{
	return LinkedList::size();
}
