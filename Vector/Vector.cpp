#include "Vector.h"
#include <cstdlib>
#include <cassert>
#include <iostream>
using namespace std;

MyVector::MyVector(size_t size, ResizeStrategy strategy, float coef)
{
	_data = nullptr;
	_size = size;
	_coef = coef;
	_strategy = strategy;
	_capacity = 1;

}

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy strategy, float coef)
{
	_size = size;
	_coef = coef;
	_strategy = strategy;

	if (strategy == ResizeStrategy::Multiplicative)
		_capacity = coef * size;

	else if (strategy == ResizeStrategy::Additive)
		_capacity = _capacity + coef;

	_data = new ValueType[_capacity];
	for (size_t i = 0; i < size; i++)
	{
		_data[i] = value;
	}
}

MyVector::MyVector(const MyVector& copy)
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

MyVector& MyVector::operator=(const MyVector& copy)
{
	if (this == &copy)
	{
		return *this;
	}

	MyVector bufVector(copy);
	this->_data = new ValueType[bufVector._capacity];
	for (size_t i = 0; i < bufVector._size; i++)
	{
		this->_data[i] = bufVector._data[i];
	}
	this->_size = bufVector._size;
	this->_coef = bufVector._coef;
	this->_strategy = bufVector._strategy;
	this->_capacity = bufVector._capacity;

	return *this;
}

MyVector::~MyVector()
{
	delete[] _data;
}

size_t MyVector::capacity() const
{
	return _capacity;
}

size_t MyVector::size() const
{
	return _size;
}

float MyVector::loadFactor()
{
	return _size / (float)_capacity;
}

ValueType& MyVector::operator[](const size_t i) const
{
	if (i < 0 || i >= this->_size)
		assert(i < 0 || i >= this->_size);
	return _data[i];
}

void MyVector::reserve(const size_t capacity)
{
	MyVector vec(*this);
	_capacity = capacity;
	this->_data = new ValueType[capacity];
	for (size_t i = 0; i < this->_size; i++)
	{
		this->_data[i] = vec._data[i];
	}
}

void MyVector::pushBack(const ValueType& value)
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
			while(loadFactor() > 1/(_coef * _coef))
				this->reserve(_capacity * _coef);
		}

		else if (_strategy == ResizeStrategy::Additive)
		{
			while(_size >= _capacity)
				this->reserve(_capacity + _coef);
		}
		
		this->_size++;
		this->_data[_size - 1] = value;
	}
}

void MyVector::insert(const size_t i, const ValueType& value)
{
	if (i < 0) {
		assert(i < 0);
	}
	else if (i > _size) {
		assert(i > _size);
	}

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
				while (loadFactor() > 1 / (_coef * _coef))
					this->reserve(_capacity * _coef);
			}

			else if (_strategy == ResizeStrategy::Additive)
			{
				while (_size >= _capacity)
					this->reserve(_capacity + _coef);
			}
		}
		MyVector vec(*this);
		this->_data = new ValueType[_size + 1];
		for (size_t k = 0; k < i; k++)
		{
			this->_data[k] = vec._data[k];
		}
		this->_data[i] = value;
		for (size_t k = i + 1; k < _size + 1; k++)
		{
			this->_data[k] = vec._data[k - 1];
		}
		++_size;
	}
}

void MyVector::insert(const size_t i, const MyVector& value)
{
	if (i < 0) {
		assert(i < 0);
	}
	else if (i > _size) {
		assert(i > _size);
	}
	else
	{
		if (_size >= _capacity)
		{
			if (_strategy == ResizeStrategy::Multiplicative)
			{
				while (loadFactor() > 1 / (_coef * _coef))
					this->reserve(_capacity * _coef);
			}

			else if (_strategy == ResizeStrategy::Additive)
			{
				while (_size >= _capacity)
					this->reserve(_capacity + _coef);
			}
		}
		MyVector vec(*this);
		this->_data = new ValueType[_size + value._size+1];
		for (size_t k = 0; k < i; k++)
		{
			this->_data[k] = vec._data[k];
		}
		for (size_t k = i; k < i + value._size; k++)
		{
			this->_data[k] = value._data[k - i];
		}
		for (size_t k = i + value._size; k < _size + value._size + 1; k++)
		{
			this->_data[k] = vec._data[k - value._size];
		}
		_size+= value._size;
	}
}

void MyVector::popBack()
{
	//if (this->_data = nullptr)
	//	assert(this->_data = nullptr);
	MyVector vec(*this);
	this->_data = new ValueType[_size - 1];
	for (size_t i = 0; i < _size - 1; i++)
	{
		this->_data[i] = vec._data[i];
	}
	--_size;
}

void MyVector::erase(const size_t i)
{
	if (i < 0) {
		assert(i < 0);
	}
	else if (i > _size) {
		assert(i > _size);
	}

	if (i == _size)
	{
		popBack();
	}

	else
	{
		MyVector vec(*this);
		this->_data = new ValueType[_size - 1];
		for (size_t k = 0; k < i; k++)
		{
			this->_data[k] = vec._data[k];
		}
		for (size_t k = i; k < _size - 1; k++)
		{
			this->_data[k] = vec._data[k + 1];
		}
		--_size;
	}
}

void MyVector::erase(const size_t i, const size_t len)
{
	if (i < 0) {
		assert(i < 0);
	}
	else if (i > _size) {
		assert(i > _size);
	}
	else
	{
		MyVector vec(*this);
		this->_data = new ValueType[_size - len];
		for (size_t k = 0; k < i; k++)
		{
			this->_data[k] = vec._data[k];
		}
		for (size_t k = i; k < _size - len; k++)
		{
			this->_data[k] = vec._data[k + len];
		}
		_size -= len;
	}

}

long long int MyVector::find(const ValueType& value, bool isBegin) const
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

void MyVector::resize(const size_t size, const ValueType value)
{
	if (size > this->_size)
	{
		MyVector vec(*this);
		this->_data = new ValueType[size];
		for (size_t i = 0; i < vec._size; i++)
		{
			this->_data[i] = vec._data[i];
		}
		for (size_t i = vec._size; i < size; i++)
		{
			this->_data[i] = value;
		}
		this->_size = size;
	}
	else if (size < this->_size)
	{
		MyVector vec(*this);
		this->_data = new ValueType[size];
		for (size_t i = 0; i < size; i++)
		{
			this->_data[i] = vec._data[i];
		}
		this->_size = size;
	}
}

void MyVector::clear()
{
	for (size_t i = 0; i < _size; i++)
	{
		_data[i] = 0;
	}
	_size = 0;
}
