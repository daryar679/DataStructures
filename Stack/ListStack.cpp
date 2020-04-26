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
	return getNode(size() - 1)->value;
}

const ValueType& ListStack::top() const
{
	return getNode(size() - 1)->value;
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
