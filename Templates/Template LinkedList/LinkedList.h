#pragma once
#include<cstdlib>

template<typename ValueType> 
class LinkedList
{
		struct Node {
		Node(const ValueType& value, Node* next = nullptr);
		~Node();

		void insertNext(const ValueType& value);
		void removeNext();

		ValueType value;
		Node* next;
	};

public:
	LinkedList();
	LinkedList(const LinkedList& copyList);
	LinkedList& operator=(const LinkedList& copyList);

	LinkedList(LinkedList&& moveList) noexcept;
	LinkedList& operator=(LinkedList&& moveList) noexcept;

	~LinkedList();
	

	ValueType& operator[](const size_t pos) const;
	LinkedList::Node* getNode(const size_t pos) const;

	void insert(const size_t pos, const ValueType& value);
	void insertAfterNode(Node* node, const ValueType& value);
	void pushBack(const ValueType& value);
	void pushFront(const ValueType& value);

	void remove(const size_t pos);
	void removeNextNode(Node* node);
	void removeFront();
	void removeBack();

	long long int findIndex(const ValueType& value) const;
	Node* findNode(const ValueType& value) const;

	void reverse();					
	LinkedList reverse() const;			
	LinkedList getReverseList() const;	
	size_t size() const;

private:
	Node* _head;
	size_t _size;

	void forceNodeDelete(Node* node);
};

template<typename ValueType> 
LinkedList<ValueType>::Node::Node(const ValueType& value, Node* next)
{
	this->value = value;
	this->next = next;
}

template<typename ValueType> 
LinkedList<ValueType>::Node::~Node()
{
	// ничего не удаляем, т.к. агрегация
}

template<typename ValueType> 
void LinkedList<ValueType>::Node::insertNext(const ValueType& value)
{
	Node* newNode = new Node(value, this->next);
	this->next = newNode;
}

template<typename ValueType> 
void LinkedList<ValueType>::Node::removeNext()
{
	if ((this->next == nullptr)||(this->next->next==nullptr))
	{
		return;
	}
	Node* removeNode = this->next;
	Node* newNext = removeNode->next;
	delete removeNode;
	this->next = newNext;
}

template<typename ValueType>
LinkedList<ValueType>::LinkedList()
	: _head(nullptr), _size(0)
{

}

template<typename ValueType>
LinkedList<ValueType>::LinkedList(const LinkedList& copyList)
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

template<typename ValueType>
LinkedList<ValueType>& LinkedList<ValueType>::operator=(const LinkedList& copyList)
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

template<typename ValueType>
LinkedList<ValueType>::LinkedList(LinkedList&& moveList) noexcept
{
	this->_size = moveList._size;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._head = nullptr;
}

template<typename ValueType>
LinkedList<ValueType>& LinkedList<ValueType>::operator=(LinkedList&& moveList) noexcept
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

template<typename ValueType>
LinkedList<ValueType>::~LinkedList()
{
	forceNodeDelete(_head);
}

template<typename ValueType>
ValueType& LinkedList<ValueType>::operator[](const size_t pos) const
{
	return getNode(pos)->value;
}

template<typename ValueType>
LinkedList<ValueType>::Node* LinkedList<ValueType>::getNode(const size_t pos) const
{
	assert(pos >= 0 && pos <= _size);

	Node* bufNode = this->_head;
	for (int i = 0; i < pos; ++i) {
		bufNode = bufNode->next;
	}

	return bufNode;
}

template<typename ValueType>
void LinkedList<ValueType>::insert(const size_t pos, const ValueType& value)
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

template<typename ValueType>
void LinkedList<ValueType>::insertAfterNode(Node* node, const ValueType& value)
{
	node->insertNext(value);
	++_size;
}

template<typename ValueType>
void LinkedList<ValueType>::pushBack(const ValueType& value)
{
	if (_size == 0) {
		pushFront(value);
		return;
	}
	insert(_size, value);
}

template<typename ValueType>
void LinkedList<ValueType>::pushFront(const ValueType& value)
{
	_head = new Node(value, _head);
	++_size;
}

template<typename ValueType>
void LinkedList<ValueType>::remove(const size_t pos)
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

template<typename ValueType>
void LinkedList<ValueType>::removeNextNode(Node* node)
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

template<typename ValueType>
void LinkedList<ValueType>::removeFront()
{
	if (_size == 0)
		return;
	else
		remove(0);
	/*Node* bufNode = _head;
	_head = _head->next;
	delete bufNode;
	_size--;*/
}

template<typename ValueType>
void LinkedList<ValueType>::removeBack()
{
	if (_size == 0)
		return;
	else
		remove(_size - 1);
}

template<typename ValueType>
long long int LinkedList<ValueType>::findIndex(const ValueType& value) const
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

template<typename ValueType>
LinkedList<ValueType>::Node* LinkedList<ValueType>::findNode(const ValueType& value) const
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

template<typename ValueType>
void LinkedList<ValueType>::reverse()
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

template<typename ValueType>
LinkedList<ValueType> LinkedList<ValueType>::reverse() const
{
	LinkedList newList (*this);
	newList.reverse();
	return newList;
}

template<typename ValueType>
LinkedList<ValueType> LinkedList<ValueType>::getReverseList() const
{
	LinkedList newList =*this;
	newList.reverse();
	return newList;
}

template<typename ValueType>
size_t LinkedList<ValueType>::size() const
{
	return _size;
}

template<typename ValueType>
void LinkedList<ValueType>::forceNodeDelete(Node* node)
{
	if (node == nullptr) {
		return;
	}

	Node* nextDeleteNode = node->next;
	delete node;
	forceNodeDelete(nextDeleteNode);
}
