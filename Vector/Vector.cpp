﻿#include "Vector.h"
#include <cstdlib>
#include <cassert>
#include <iostream>
using namespace std;

MyVector::MyVector(size_t size, ResizeStrategy strategy, float coef)
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
}

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy strategy, float coef)
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
	std::swap(this->_size, bufVector._size);
	std::swap(this->_coef, bufVector._coef);
	std::swap(this->_strategy, bufVector._strategy);
	std::swap(this->_capacity, bufVector._capacity);
	std::swap(this->_data, bufVector._data);

	return *this;
}

MyVector::~MyVector()
{
	if (_data != nullptr)
	{
		delete[] _data;
		_data = nullptr;
	}
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
	assert((i >= 0) && (i < this->_size));
	return _data[i];
}

void MyVector::reserve(const size_t capacity)
{
	MyVector vec(*this);
	_capacity = capacity;
	delete[] _data; 
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
				this->reserve(_capacity * _coef);
		}

		else if (_strategy == ResizeStrategy::Additive)
		{
				this->reserve(_capacity + _coef);
		}

		this->_size++;
		this->_data[_size - 1] = value;
	}
}

void MyVector::insert(const size_t i, const ValueType& value)
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
					this->reserve(_capacity * _coef);
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
}

void MyVector::insert(const size_t i, const MyVector& value)
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
}

void MyVector::popBack()
{
	if (this->_data == nullptr)
		return;
	--_size;
}

void MyVector::erase(const size_t i)
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
}

void MyVector::erase(const size_t i, const size_t len)
{
	assert((i >= 0) && (i <= _size));
	
		for (size_t k = i; k < _size - len; k++)
		{
			this->_data[k] = this->_data[k + len];
		}
		_size -= len;
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
}


void MyVector::clear()
{
	for (size_t i = 0; i < _size; i++)
	{
		_data[i] = 0;
	}
	_size = 0;
}
