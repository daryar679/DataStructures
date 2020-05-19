#pragma once
#include "StackImplementation.h"
#include "Vector.h" // меняете на include вашего вектора

// вариант с использованием ранее написанного вектора и множественного наследования
// если бы вектор не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
class VectorStack : public StackImplementation, public MyVector
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

