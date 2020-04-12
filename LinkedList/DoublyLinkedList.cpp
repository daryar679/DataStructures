#include "DoublyLinkedList.h"

#include <cassert>

DoublyLinkedList::Node::Node(const ValueType& value, Node* next, Node* prev)
{
	this->value = value;
	this->next = next;
	this->prev = prev;
}

DoublyLinkedList::Node::~Node()
{
	// ничего не удаляем, т.к. агрегация
}

void DoublyLinkedList::Node::insertNext(const ValueType& value)
{
	Node* newNode = new Node(value,this->next,this);
	this->next = newNode;
}

void DoublyLinkedList::Node::removeNext()
{
	Node* removeNode = this->next;
	Node* newNext = removeNode->next;
	delete removeNode;
	newNext->prev = this;
	this->next = newNext;
}

DoublyLinkedList::DoublyLinkedList()
	: _head(nullptr), _size(0),_tail(nullptr)
{

}

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& copyList)
{
	this->_size = copyList._size;
	if (this->_size == 0) {
		this->_head = nullptr;
		this->_tail = nullptr;
		return;
	}

	this->_head = new Node(copyList._head->value);

	Node* currentNode = this->_head;
	Node* currentCopyNode = copyList._head;

	while (currentCopyNode->next) {
		currentNode->next = new Node(currentCopyNode->value);
		currentCopyNode = currentCopyNode->next;
		currentNode = currentNode->next;
	}
	this->_tail = currentNode;
}

DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& copyList)
{
	if (this == &copyList) {
		return *this;
	}
	forceNodeDelete(_head);
	DoublyLinkedList bufList(copyList);
	this->_size = bufList._size;
	this->_head = bufList._head;
	this->_tail = bufList._tail;

	return *this;
}

DoublyLinkedList::DoublyLinkedList(DoublyLinkedList&& moveList) noexcept
{
	this->_size = moveList._size;
	this->_head = moveList._head;
	this->_tail = moveList._tail;

	moveList._size = 0;
	moveList._head = nullptr;
	moveList._tail = nullptr;
}

DoublyLinkedList& DoublyLinkedList::operator=(DoublyLinkedList&& moveList) noexcept
{
	if (this == &moveList) {
		return *this;
	}
	forceNodeDelete(_head);
	this->_size = moveList._size;
	this->_head = moveList._head;
	this->_tail = moveList._tail;

	moveList._size = 0;
	moveList._head = nullptr;
	moveList._tail = nullptr;

	return *this;
}

DoublyLinkedList::~DoublyLinkedList()
{
	forceNodeDelete(_head);
}

ValueType& DoublyLinkedList::operator[](const size_t pos) const
{
	return getNode(pos)->value;
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(const size_t pos) const
{
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos >= this->_size) {
		assert(pos >= this->_size);
	}

	Node* bufNode = this->_head;
	for (int i = 0; i < pos; ++i) {
		bufNode = bufNode->next;
	}

	return bufNode;
}

void DoublyLinkedList::insert(const size_t pos, const ValueType& value)
{
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos > this->_size) {
		assert(pos > this->_size);
	}

	if (pos == 0) {
		pushFront(value);
	}
	if (pos == _size-1) {
		pushBack(value);
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

void DoublyLinkedList::insertAfterNode(Node* node, const ValueType& value)
{
	if (node == nullptr)
	{
		return;
	}
	node->insertNext(value);
}

void DoublyLinkedList::pushBack(const ValueType& value)
{
	if (_size == 0) {
		pushFront(value);
		return;
	}

	Node* new_tail = new Node(value, nullptr, _tail);
	if (_tail != nullptr)
		_tail->next = new_tail;
	_tail = new_tail;
	++_size;
}

void DoublyLinkedList::pushFront(const ValueType& value)
{
	Node* new_head = new Node(value, _head, nullptr);
	if (_size == 0)
		_head = _tail = new_head;
	else if (_head != nullptr)
		_head->prev = new_head;
	_head = new_head;
	++_size;
}

void DoublyLinkedList::remove(const size_t pos)
{
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos > this->_size) {
		assert(pos > this->_size);
	}

	if (pos == 0){
		removeFront();
	}
	if (pos == _size - 1){
		removeBack();
	}
	else
	{
		Node* bufNode = this->_head;
		for (size_t i = 0; i < pos - 1; ++i) {
			bufNode = bufNode->next;
		}
		Node* deleteNode = bufNode->next;
		bufNode->next = deleteNode->next;
		deleteNode->next->prev = bufNode;
		delete deleteNode;
		--_size;
	}
}

void DoublyLinkedList::removeNextNode(Node* node)
{
	if (node->next == nullptr)
	{
		assert(node->next == nullptr);
	}
	Node* deleteNode = node->next;
	Node* bufNode = deleteNode->next;
	node->next = bufNode;
	bufNode->prev = node;
	delete deleteNode;
	--_size;
}

void DoublyLinkedList::removeFront()
{
	Node* bufNode = _head;
	_head = _head->next;
	delete bufNode;
	_size--;
}

void DoublyLinkedList::removeBack()
{
	Node* bufNode = _tail;
	_tail = _tail->prev;
	delete bufNode;
	_size--;
}

long long int DoublyLinkedList::findIndex(const ValueType& value) const
{
	long long index = 0;
	Node* bufNode = _head;
	for (index = 0; index < _size - 1; index++)
	{
		if (bufNode->value == value)
		{
			return index;
		}
		bufNode = bufNode->next;
	}
	return -1;
}

DoublyLinkedList::Node* DoublyLinkedList::findNode(const ValueType& value) const
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

void DoublyLinkedList::reverse()
{
	Node* current = _head;
	Node* bufNode = nullptr;
	while (current != nullptr)
	{
		bufNode = current->prev;
		current->prev = current->next;
		current->next = bufNode;
		current = current->prev;
	}
	if (bufNode != nullptr)
		_head = bufNode->prev;
}

DoublyLinkedList DoublyLinkedList::reverse() const
{
	DoublyLinkedList newList = *this;
	newList.reverse();
	return newList;
}

DoublyLinkedList DoublyLinkedList::getReverseList() const
{
	DoublyLinkedList newList = *this;
	Node* current = newList. _head;
	Node* bufNode = nullptr;
	while (current != nullptr)
	{
		bufNode = current->prev;
		current->prev = current->next;
		current->next = bufNode;
		current = current->prev;
	}
	if (bufNode != nullptr)
		newList._head = bufNode->prev;

	return newList;
}

size_t DoublyLinkedList::size() const
{
	return _size;
}

void DoublyLinkedList::forceNodeDelete(Node* node)
{
	if (node == nullptr) {
		return;
	}

	Node* nextDeleteNode = node->next;
	delete node;
	forceNodeDelete(nextDeleteNode);
}
int main()
{
	return 0;
}
