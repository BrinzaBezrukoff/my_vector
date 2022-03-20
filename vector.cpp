//
// Created by brinza on 11.03.2022.
//

#include <algorithm>
#include <iostream>

#include "vector.h"


Vector::Vector(const Value *rawArray, const size_t size, float coef) {
    std::cout << "raw constructor" << std::endl;
    _capacity = size;
    _size = size;
    _multiplicativeCoef = coef;
    _data = new Value[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = rawArray[i];
    }
}

Vector::~Vector() {
    std::cout << "destructor" << std::endl;
    _capacity = 0;
    _size = 0;
    delete [] _data;
}

Vector::Vector(const Vector &other) {
    std::cout << "copy constructor" << std::endl;
    delete [] _data;
    _capacity = other._capacity;
    _size = other._size;
    _data = new Value[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = other._data[i];
    }
}

Vector &Vector::operator=(const Vector &other) {
    std::cout << "copy =" << std::endl;
    if (&other == this) {
        return *this;
    }
    Vector buff (other);
    std::swap(this->_data, buff._data);
    return *this;
}

Vector::Vector(Vector &&other) noexcept {
    std::cout << "move constructor" << std::endl;
    delete [] _data;
    _capacity = other._capacity;
    _size = other._size;
    _data = other._data;
    other._data = nullptr;
    other._capacity = 0;
    other._size = 0;
}

Vector &Vector::operator=(Vector &&other) noexcept {
    std::cout << "move =" << std::endl;
    if (&other == this) {
        return *this;
    }
    Vector buff (std::move(other));
    std::swap(this->_data, buff._data);
    return *this;
}

void Vector::pushBack(const Value &value) {
    extendData(_size + 1);
    _data[_size] = value;
    _size += 1;
}

void Vector::pushFront(const Value &value) {
    extendData(_size + 1);
    for (int i = 0; i < _size; i++) {
        _data[i + 1] = _data[i];
    }
    _data[0] = value;
}

void Vector::extendData(size_t newSize) {
    if (_capacity >= newSize) {
        return;
    }
    while (_capacity < newSize) {
        _capacity = static_cast<size_t>(static_cast<float>(_capacity) * _multiplicativeCoef + 1);
    }
    auto *newData = new Value[_capacity];
    for (int i = 0; i < _size; i++) {
        newData[i] = _data[i];
    }
    delete [] _data;
    _data = newData;
}

size_t Vector::size() const {
    return _size;
}
