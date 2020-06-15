# pragma once
#include <cstdlib>
#include <cassert>
#include <iostream>

enum class ResizeStrategy {
	Additive,
	Multiplicative
};

enum class SortedStrategy {
	Increase,
	Decrease
};

template<typename ValueType>

class MyVector
{
public:
	MyVector(size_t size = 0, ResizeStrategy = ResizeStrategy::Multiplicative, float coef = 1.5f);
	MyVector(size_t size, ValueType value, ResizeStrategy = ResizeStrategy::Multiplicative, float coef = 1.5f);

	MyVector(const MyVector& copy);
	MyVector& operator= (const MyVector& copy);

	~MyVector();

	size_t capacity() const;
	size_t size() const;
	float loadFactor();

	ValueType& operator[](const size_t i) const;

	void pushBack(const ValueType& value);
	void insert(const size_t i, const ValueType& value);		
	void insert(const size_t i, const MyVector& value);		
	void popBack();
	void erase(const size_t i);
	void erase(const size_t i, const size_t len);			
	long long int find(const ValueType& value, bool isBegin = true) const;

	void reserve(const size_t capacity);
	void resize(const size_t size, const ValueType = 0.0);
	void allocationOfCap();
	void clear();
	//static MyVector sortedSquares(MyVector& vec, SortedStrategy strategy);

	class Iterator
	{
	public:
		Iterator(ValueType* p) : ptr(p) {};
		ValueType& operator*() { return *ptr; };
		ValueType* operator->() { return ptr; };
		Iterator operator++() { return ++ptr; };
		Iterator operator++(int) { return ptr++; };
		Iterator operator-(int a) { return ptr - a; };
		Iterator operator+(int a) { return ptr + a; };
		Iterator operator--(int) { return ptr--; };
		Iterator operator--() { return --ptr; };
		bool operator==(Iterator& b) { return ptr == b.ptr; };
		bool operator!=(Iterator& b) { return ptr != b.ptr; };
		bool operator<(Iterator& b) { return ptr < b.ptr; };
		bool operator>(Iterator& b) { return ptr > b.ptr; };
	private:
		ValueType* ptr;
	};
	Iterator begin() { return this->_data; };
	Iterator end() { return this->_data + this->_size; };

private:
	ValueType* _data;
	size_t _size;
	size_t _capacity;
	ResizeStrategy _strategy;
	float _coef;
	//friend MyVector sortedSquares(MyVector& vec, SortedStrategy strategy);
};

template<typename ValueType>
MyVector<ValueType>::MyVector(size_t size, ResizeStrategy strategy, float coef)
{
	_size = size;
	_coef = coef;
	_strategy = strategy;
	
	if ((strategy == ResizeStrategy::Multiplicative) && (_size != 0))
		_capacity = coef * size;

	else if ((strategy == ResizeStrategy::Additive) && (_size != 0))
		_capacity = coef + size;

	else if (_size == 0)
		_capacity = 1;

	_data = new ValueType[_capacity];
	for (size_t i = 0; i < size; i++)
		{
			_data[i] = 0;
		}
}

template<typename ValueType>
MyVector<ValueType>::MyVector(size_t size, ValueType value, ResizeStrategy strategy, float coef)
{
	_size = size;
	_coef = coef;
	_strategy = strategy;

	if (strategy == ResizeStrategy::Multiplicative)
		_capacity = coef * size;

	else if (strategy == ResizeStrategy::Additive)
		_capacity = coef + size;

	_data = new ValueType[_capacity];
	for (size_t i = 0; i < size; i++)
	{
		_data[i] = value;
	}
}

template<typename ValueType>
MyVector<ValueType>::MyVector(const MyVector& copy)
{
	this->_data = new ValueType[copy._capacity];
	for (size_t i = 0; i < copy._size; i++)
	{
		this->_data[i] = copy._data[i];
	}
	this->_size = copy._size;
	this->_coef = copy._coef;
	this->_strategy = copy._strategy;
	this->_capacity = copy._capacity;

}

template<typename ValueType>
MyVector<ValueType>& MyVector<ValueType>::operator=(const MyVector& copy)
{
	if (this == &copy)
	{
		return *this;
	}
	MyVector bufVector(copy);
	std::swap(this->_size, bufVector._size);
	std::swap(this->_coef, bufVector._coef);
	std::swap(this->_strategy, bufVector._strategy);
	std::swap(this->_capacity, bufVector._capacity);
	std::swap(this->_data, bufVector._data);

	return *this;
}

template<typename ValueType>
MyVector<ValueType>::~MyVector()
{
	if (_data != nullptr)
	{
		delete[] _data;
		_data = nullptr;
	}
}

template<typename ValueType>
size_t MyVector<ValueType>::capacity() const
{
	return _capacity;
}

template<typename ValueType>
size_t MyVector<ValueType>::size() const
{
	return _size;
}

template<typename ValueType>
float MyVector<ValueType>::loadFactor()
{
	return _size / (float)_capacity;
}

template<typename ValueType>
ValueType& MyVector<ValueType>::operator[](const size_t i) const
{
	assert((i >= 0) && (i < this->_size));
	return _data[i];
}

template<typename ValueType>
void MyVector<ValueType>::reserve(const size_t capacity)
{
	MyVector vec = *this;
	_capacity = capacity;
	delete[] _data;
	this->_data = new ValueType[capacity];
	for (size_t i = 0; i < this->_size; i++)
	{
		this->_data[i] = vec._data[i];
	}
}

template<typename ValueType>
void MyVector<ValueType>::pushBack(const ValueType& value)
{
	if (_size < _capacity)
	{
		_data[_size] = value;
		++_size;
	}
	else if (_size >= _capacity)
	{
		if (_strategy == ResizeStrategy::Multiplicative)
		{
				this->reserve(_capacity * _coef *_coef);
		}

		else if (_strategy == ResizeStrategy::Additive)
		{
				this->reserve(_capacity + _coef);
		}

		this->_size++;
		this->_data[_size - 1] = value;
	}
	allocationOfCap();
}

template<typename ValueType>
void MyVector<ValueType>::insert(const size_t i, const ValueType& value)
{
	assert((i >= 0) && (i < _size + 1));

	if (i == _size)
	{
		pushBack(value);
	}
	else
	{
		if (_size >= _capacity)
		{
			if (_strategy == ResizeStrategy::Multiplicative)
			{
					this->reserve(_capacity * _coef *_coef);
			}

			else if (_strategy == ResizeStrategy::Additive)
			{
					this->reserve(_capacity + _coef);
			}
		}
		for (size_t k = _size; k > i; k--)
		{
			this->_data[k] = this->_data[k - 1];
		}
		this->_data[i] = value;
		++_size;
	}
	allocationOfCap();
}

template<typename ValueType>
void MyVector<ValueType>::insert(const size_t i, const MyVector& value)
{
	assert((i >= 0) && (i <= _size));

		if ((_size+value._size) >= _capacity)
		{
			if (_strategy == ResizeStrategy::Multiplicative)
			{
					this->reserve((_size+value._size) * _coef);
			}

			else if (_strategy == ResizeStrategy::Additive)
			{
					this->reserve(_size + value._size + _coef);
			}
		}
		for (size_t k = _size + value._size; k > value._size; k--)
		{
			this->_data[k] = this->_data[k - value._size];
		}
		for (size_t k = i; k < i + value._size; k++)
		{
			this->_data[k] = value._data[k - i];
		}
		_size += value._size;
		allocationOfCap();
}

template<typename ValueType>
void MyVector<ValueType>::popBack()
{
	if (this->_data == nullptr)
		return;
	--_size;
	allocationOfCap();
}

template<typename ValueType>
void MyVector<ValueType>::erase(const size_t i)
{
	assert((i >= 0) && (i <= _size));

	if (i == _size)
	{
		popBack();
	}

	else
	{
		for (size_t k = i; k < _size - 1; k++)
		{
			this->_data[k] = this->_data[k + 1];
		}
		--_size;
	}
	allocationOfCap();
}

template<typename ValueType>
void MyVector<ValueType>::erase(const size_t i, const size_t len)
{
	assert((i >= 0) && (i <= _size));
	
		for (size_t k = i; k < _size - len; k++)
		{
			this->_data[k] = this->_data[k + len];
		}
		_size -= len;
		allocationOfCap();
}

template<typename ValueType>
long long int MyVector<ValueType>::find(const ValueType& value, bool isBegin) const
{
	if (isBegin)
	{
		for (size_t i = 0; i < _size; i++)
		{
			if (_data[i] == value)
			{
				return i;
			}
		}
	}
	else
	{
		for (size_t i = _size - 1; i > 0; i--)
		{
			if (_data[i] == value)
			{
				return i;
			}
		}
	}
	return -1;
}

template<typename ValueType>
void MyVector<ValueType>::resize(const size_t size, const ValueType value)
{
	if (size > this->_size)
	{
		if ((_strategy == ResizeStrategy::Multiplicative))
				reserve(size * _coef);

		else if ((_strategy == ResizeStrategy::Additive))
			reserve(size +_coef);

		for (size_t i = this->_size; i < size; i++)
		{
			this->_data[i] = value;
		}
		this->_size = size;
	}
	else if (size < this->_size)
	{
		MyVector vec(*this);
		delete[] _data;
		this->_data = new ValueType[size];
		for (size_t i = 0; i < size; i++)
		{
			this->_data[i] = vec._data[i];
		}
		this->_size = size;
		if ((_strategy == ResizeStrategy::Multiplicative))
			reserve(size * _coef);

		else if ((_strategy == ResizeStrategy::Additive))
			reserve(size + _coef);
	}
	allocationOfCap();
}

template<typename ValueType>
void MyVector<ValueType>::allocationOfCap()
{
	if (loadFactor() < (1 / (_coef * _coef)) || loadFactor() > 1)
	{
		if ((_strategy == ResizeStrategy::Multiplicative) && (_size != 0))
		{
			this->reserve(_size * _coef);
		}

		else if ((_strategy == ResizeStrategy::Additive) && (_size != 0))
		{
			this->reserve(_size + _coef);
		}
		else if (_size == 0)
		{
			this->reserve(1);
		}
	}
}

template<typename ValueType>
void MyVector<ValueType>::clear()
{
	for (size_t i = 0; i < _size; i++)
	{
		_data[i] = 0;
	}
	_size = 0;
}

/*template<typename ValueType>
MyVector<ValueType> sortedSquares(MyVector& vec, SortedStrategy strategy)
{
	MyVector sort(vec);
	size_t start = 0;
	size_t finish = vec.size() - 1;
	if (strategy == SortedStrategy::Decrease)
	{
		for(size_t i = 0; i < vec._size; i++)
		{
			if (abs(vec._data[start]) > abs(vec._data[finish]))
			{
				sort._data[i] = pow(vec._data[start], 2);
				++start;
			}
			else
			{
				sort._data[i] = pow(vec._data[finish], 2);
				--finish;
			}
		}
	}
	else
	{
		for (size_t i = vec._size-1; i > 0; i--)
		{
			if (abs(vec._data[start]) > abs(vec._data[finish]))
			{
				sort._data[i] = pow(vec._data[start], 2);
				++start;
			}
			else
			{
				sort._data[i] = pow(vec._data[finish], 2);
				--finish;
			}
		}
	}
	return sort;
}*/
