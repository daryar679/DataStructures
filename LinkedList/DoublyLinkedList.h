#pragma once

// ����� �������� �� �������
using ValueType = double;

class DoublyLinkedList
{
	// ����� ���� ������
	// �� ����� ����, ����� ��������� ����� ������,
	// ����� ����������� � ������������� ������, ������ ������� 
	// ���� � ������ � ���� �, � ������ �����, �������� ������ LinkedList 
	// (������ �� �����, ����� �� ����� � �.�.)
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

	// ������ � �������� �������� �� �������
	ValueType& operator[](const size_t pos) const;
	// ������ � ���� �� �������
	DoublyLinkedList::Node* getNode(const size_t pos) const;

	// ������� �������� �� �������, ������� ����, ���� ��������� (�(n)), ����� ��������� (O(1))
	void insert(const size_t pos, const ValueType& value);
	// ������� �������� ����� ����, (O(1))
	static void insertAfterNode(Node* node, const ValueType& value);
	// ������� � ����� (�(n))
	void pushBack(const ValueType& value);
	// ������� � ������ (�(1))
	void pushFront(const ValueType& value);

	// ��������
	void remove(const size_t pos);
	void removeNextNode(Node* node);
	void removeFront();
	void removeBack();

	// �����, �(n)
	long long int findIndex(const ValueType& value) const;
	Node* findNode(const ValueType& value) const;

	// �������� ������
	void reverse();						// ��������� �������� ������
	DoublyLinkedList reverse() const;			// �������� ������ ������ (��� ����������� ��������)
	DoublyLinkedList getReverseList() const;	// ����� ������������� ������ ���� ��� ���������� ����� ����������� ������

	size_t size() const;
private:
	Node* _head;
	Node* _tail;
	size_t	_size;

	void forceNodeDelete(Node* node);
};
