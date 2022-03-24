//
// Created by brinza on 11.03.2022.
//

#include <algorithm>

#include "vector.h"


Vector::Vector():
    _capacity(1),
    _size(0),
    _multiplicativeCoef(2.0)
{
    _data = new Value[_capacity];
}

Vector::Vector(const Value *rawArray, const size_t size, float coef):
    Vector()
{
    _multiplicativeCoef = coef;
    newSize(size);
    for (int i = 0; i < _size; i++) {
        _data[i] = rawArray[i];
    }
}

Vector::Vector(const Vector &other) {
    delete [] _data;
    _capacity = other._capacity;
    _size = other._size;
    _data = new Value[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = other._data[i];
    }
}

Vector &Vector::operator=(const Vector &other) {
    if (&other == this) {
        return *this;
    }
    Vector buff (other);
    std::swap(this->_data, buff._data);
    return *this;
}

Vector::Vector(Vector &&other) noexcept {
    delete [] _data;
    _capacity = other._capacity;
    _size = other._size;
    _data = other._data;
    other._data = nullptr;
    other._capacity = 0;
    other._size = 0;
}

Vector &Vector::operator=(Vector &&other) noexcept {
    if (&other == this) {
        return *this;
    }
    Vector buff (std::move(other));
    std::swap(this->_data, buff._data);
    return *this;
}

Vector::~Vector() {
    _capacity = 0;
    _size = 0;
    delete [] _data;
}

void Vector::pushBack(const Value &value) {
    newSize(_size + 1);
    _data[_size - 1] = value;
}

void Vector::pushFront(const Value &value) {
    makeGap(0, 1);
    _data[0] = value;
}

void Vector::insert(const Value& value, size_t pos) {
    makeGap(pos, 1);
    _data[pos] = value;
}

void Vector::insert(const Value* values, size_t size, size_t pos) {
    makeGap(pos, size);
    for (size_t i = 0; i < size; i++) {
        _data[pos + i] = values[i];
    }
}

void Vector::insert(const Vector& vector, size_t pos) {
    makeGap(pos, vector.size());
    for (size_t i = 0; i < vector.size(); i++) {
        _data[pos + i] = vector[i];
    }
}

size_t Vector::size() const {
    return _size;
}

size_t Vector::capacity() const {
    return _capacity;
}

double Vector::loadFactor() const {
    return static_cast<double>(_size) / static_cast<double>(_capacity);
}

Value& Vector::operator[](size_t idx) {
    return _data[idx];
}

const Value& Vector::operator[](size_t idx) const {
    return _data[idx];
}


void Vector::reserve(size_t capacity) {
    if (capacity <= _capacity) {
        return;
    }
    newCapacity(capacity);
}

void Vector::shrinkToFit() {
    newCapacity(_size);
}

void swap(Vector& l, Vector& r) {
    using std::swap;
    swap(l._data, r._data);
    swap(l._capacity, r._capacity);
    swap(l._size, r._size);
    swap(l._multiplicativeCoef, r._multiplicativeCoef);
}

void Vector::newSize(size_t newSize) {
    _size = newSize;
    double lf = loadFactor();
    if (lf * _multiplicativeCoef > 1) {
        reserve(_multiplicativeCoef * _size);
    }
}

void Vector::newCapacity(size_t newCapacity) {
    Value* newData = new Value[newCapacity];
    _capacity = newCapacity;
    if (_data != nullptr) {
        for (int i = 0; i < _size; i++) {
            newData[i] = _data[i];
        }
        delete[] _data;
    }
    _data = newData;
}


void Vector::makeGap(size_t pos, size_t len) {
    if (len == 0) {
        return;
    }
    newSize(_size + len);
    for (size_t i = _size - 1; i >= pos + len; i--) {
        _data[i] = _data[i - len];
    }
}

