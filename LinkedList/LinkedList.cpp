#include "LinkedList.h"

#include <cassert>

LinkedList::Node::Node(const ValueType& value, Node* next)
{
	this->value = value;
	this->next = next;
}

LinkedList::Node::~Node()
{
	// ничего не удаляем, т.к. агрегация
}

void LinkedList::Node::insertNext(const ValueType& value)
{
	Node* newNode = new Node(value, this->next);
	this->next = newNode;
}

void LinkedList::Node::removeNext()
{
	if (this->next == nullptr)
	{
		return;
	}
	Node* removeNode = this->next;
	Node* newNext = removeNode->next;
	delete removeNode;
	this->next = newNext;
}

LinkedList::LinkedList()
	: _head(nullptr), _size(0)
{

}

LinkedList::LinkedList(const LinkedList& copyList)
{
	this->_size = copyList._size;
	if (this->_size == 0) {
		this->_head = nullptr;
		return;
	}

	this->_head = new Node(copyList._head->value);

	Node* currentNode = this->_head;
	Node* currentCopyNode = copyList._head;

	while (currentCopyNode->next) {
		currentCopyNode = currentCopyNode->next;
		currentNode->next = new Node(currentCopyNode->value);
		currentNode = currentNode->next;
	}
}

LinkedList& LinkedList::operator=(const LinkedList& copyList)
{
	if (this == &copyList) {
		return *this;
	}
	
	forceNodeDelete(_head);
	this->_size = copyList._size;
	this->_head = new Node(copyList._head->value);
	Node* buf = this->_head;
	Node* bufCopy = copyList._head;

	while (bufCopy->next != nullptr)
	{
		buf->next = new Node(bufCopy->next->value);
		buf = buf->next;
		bufCopy = bufCopy->next;
	}

	return *this;
}

LinkedList::LinkedList(LinkedList&& moveList) noexcept
{
	this->_size = moveList._size;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._head = nullptr;
}

LinkedList& LinkedList::operator=(LinkedList&& moveList) noexcept
{
	if (this == &moveList) {
		return *this;
	}
	forceNodeDelete(_head);
	this->_size = moveList._size;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._head = nullptr;

	return *this;
}

LinkedList::~LinkedList()
{
	forceNodeDelete(_head);
}

ValueType& LinkedList::operator[](const size_t pos) const
{
	return getNode(pos)->value;
}

LinkedList::Node* LinkedList::getNode(const size_t pos) const
{
	assert(pos >= 0 && pos <= _size);
	
	Node* bufNode = this->_head;
	for (int i = 0; i < pos; ++i) {
		bufNode = bufNode->next;
	}

	return bufNode;
}

void LinkedList::insert(const size_t pos, const ValueType& value)
{
	assert(pos >= 0 && pos <= _size);

	if (pos == 0) {
		pushFront(value);
	}
	else {
		Node* bufNode = this->_head;
		for (size_t i = 0; i < pos - 1; ++i) {
			bufNode = bufNode->next;
		}
		bufNode->insertNext(value);
		++_size;
	}
}

void LinkedList::insertAfterNode(Node* node, const ValueType& value)
{
	node->insertNext(value);
	++_size;
}

void LinkedList::pushBack(const ValueType& value)
{
	if (_size == 0) {
		pushFront(value);
		return;
	}
	insert(_size, value);
}

void LinkedList::pushFront(const ValueType& value)
{
	_head = new Node(value, _head);
	++_size;
}

void LinkedList::remove(const size_t pos)
{
	assert(pos >= 0 && pos < _size);
	if (pos == 0)
	{
		Node* bufNode = _head;
		_head = _head->next;
		delete bufNode;
		_size--;
	}
	else
	{
		Node* bufNode = this->_head;
		for (size_t i = 0; i < pos - 1; ++i) {
			bufNode = bufNode->next;
		}
		Node* deleteNode = bufNode->next;
		bufNode->next = deleteNode->next;
		delete deleteNode;
		_size--;
	}
}

void LinkedList::removeNextNode(Node* node)
{
	if (node->next == nullptr)
	{
		return;
	}
	Node* bufNode = node->next;
	node->next = bufNode->next;
	delete bufNode;
	_size--;
}

void LinkedList::removeFront()
{
	if (_size == 0)
		return;
	else
		remove(0);
}

void LinkedList::removeBack()
{
	if (_size == 0)
		return;
	else
		remove(_size - 1);
}

long long int LinkedList::findIndex(const ValueType& value) const
{
	long long index;
	Node* bufNode = _head;
	for (index = 0; index < _size - 1; index++)
	{
		if (bufNode->value == value)
		{
			return index;
		}
		bufNode = bufNode->next;
	}
	return 0;
}

LinkedList::Node* LinkedList::findNode(const ValueType& value) const
{
	Node* bufNode = _head;
	for (int index = 0; index < _size - 1; index++)
	{
		if (bufNode->value == value)
		{
			return bufNode;
		}
		bufNode = bufNode->next;
	}
	return nullptr;
}

void LinkedList::reverse()
{
	Node* bufNode = _head;
	Node* next = nullptr;
	Node* prev = nullptr;
	while (bufNode != nullptr)
	{
		next = bufNode->next;
		bufNode->next = prev;
		prev = bufNode;
		bufNode = next;
	}
	_head = prev;
}

LinkedList LinkedList::reverse() const
{
	LinkedList newList = *this;
	newList.getReverseList();
	return newList;
}

LinkedList LinkedList::getReverseList() const
{
	LinkedList newList = *this;
	newList.reverse();
	return newList;
}

size_t LinkedList::size() const
{
	return _size;
}

void LinkedList::forceNodeDelete(Node* node)
{
	if (node == nullptr) {
		return;
	}

	Node* nextDeleteNode = node->next;
	delete node;
	forceNodeDelete(nextDeleteNode);
}
