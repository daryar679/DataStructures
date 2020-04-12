#pragma once

// потом помен€ем на шаблоны
using ValueType = double;

class DoublyLinkedList
{
	// класс узла списка
	// по своей сути, может содержать любые данные,
	// можно реализовать и ассоциативный массив, просто добавив 
	// поле с ключем в узел и, с учетом этого, помен€ть методы LinkedList 
	// (доступ по ключу, поиск по ключу и т.д.)
	struct Node {
		Node(const ValueType& value, Node* next = nullptr, Node* prev = nullptr);
		~Node();

		void insertNext(const ValueType& value);
		void removeNext();

		ValueType value;
		Node* next;
		Node* prev;
	};

public:
	////
	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList& copyList);
	DoublyLinkedList& operator=(const DoublyLinkedList& copyList);

	DoublyLinkedList(DoublyLinkedList&& moveList) noexcept;
	DoublyLinkedList& operator=(DoublyLinkedList&& moveList) noexcept;

	~DoublyLinkedList();
	////

	// доступ к значению элемента по индексу
	ValueType& operator[](const size_t pos) const;
	// доступ к узлу по индексу
	DoublyLinkedList::Node* getNode(const size_t pos) const;

	// вставка элемента по индексу, сначала ищем, куда вставл€ть (ќ(n)), потом вставл€ем (O(1))
	void insert(const size_t pos, const ValueType& value);
	// вставка элемента после узла, (O(1))
	static void insertAfterNode(Node* node, const ValueType& value);
	// вставка в конец (ќ(n))
	void pushBack(const ValueType& value);
	// вставка в начало (ќ(1))
	void pushFront(const ValueType& value);

	// удаление
	void remove(const size_t pos);
	void removeNextNode(Node* node);
	void removeFront();
	void removeBack();

	// поиск, ќ(n)
	long long int findIndex(const ValueType& value) const;
	Node* findNode(const ValueType& value) const;

	// разворот списка
	void reverse();						// изменение текущего списка
	DoublyLinkedList reverse() const;			// полчение нового списка (дл€ константных объектов)
	DoublyLinkedList getReverseList() const;	// чтобы неконстантный объект тоже мог возвращать новый развернутый список

	size_t size() const;
private:
	Node* _head;
	Node* _tail;
	size_t	_size;

	void forceNodeDelete(Node* node);
};
