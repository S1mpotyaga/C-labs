#include "my_vector.hpp"
#include <stdexcept>
#include <iostream>


MyVector::MyVector() {
	int init_capacity = 2;
	_capacity = init_capacity;
	_size = 0;
	_data = new int[_capacity];
	
}
MyVector::MyVector(std::size_t init_capacity) {
	_capacity = init_capacity;
	_size = 0;
	_data = new int[_capacity];
}
MyVector::~MyVector() {
	delete[] _data;
}

void MyVector::set(std::size_t index, int value) {
	if (index < _size) _data[index] = value;
	else
		throw std::runtime_error("too large index for set");
}
int MyVector:: get(std::size_t index) {
	if (index < _size) return _data[index];
	else
		throw new std::runtime_error("too large index for get");
}

std::size_t MyVector::size() {
	return _size;
}

std::size_t MyVector::capacity() {
	return _capacity;
}

void MyVector::reserve(std::size_t new_capacity) {
	if (new_capacity <= _capacity) return;

	int* new_data = new int[new_capacity];
	for (std::size_t i = 0; i < _size; i++)
		new_data[i] = _data[i];
	delete[] _data;
	_data = new_data;
	_capacity = new_capacity;
}
void MyVector::resize(std::size_t new_size) {
	if (new_size < _size) {
		_size = new_size;
		return;
	}
	if (new_size > _capacity)
		reserve(std::max(new_size, _capacity * 2));
	for (std::size_t i = _size; i < new_size; i++) _data[i] = 0;
	_size = new_size;
}

void MyVector::push_back(int value) {
	if (_size == _capacity) reserve(_capacity * 2);
	_data[_size++] = value;
}

void MyVector::insert(std::size_t index, int value) {
	if (_size == _capacity) reserve(_capacity * 2);
	for (std::size_t i = _size - 1; i >= index; i--) {
		_data[i + 1] = _data[i];
	}
	_size++;
	_data[index] = value;
}
void MyVector::erase(std::size_t index) {
	if (_size == 0) throw new std::runtime_error("Erase from empty vector");
	if (index >= _size) throw new std::runtime_error("Incorrect index in erase");
	for (std::size_t i = index; i < _size - 1; i++) _data[i] = _data[i + 1];
	_size--;
}
