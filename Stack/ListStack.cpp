#include "ListStack.h"
#include "LinkedList.h"

ListStack::ListStack(const ListStack& copyList):LinkedList(copyList)
{
}

void ListStack::push(const ValueType& value)
{
	this->pushFront(value);
}

void ListStack::pop()
{
	this->removeFront();
}

ValueType& ListStack::top()
{
	return getNode(0)->value;
}

const ValueType& ListStack::top() const
{
	return getNode(0)->value;
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
