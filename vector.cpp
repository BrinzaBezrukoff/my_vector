//
// Created by brinza on 11.03.2022.
//

#include <algorithm>

#include "vector.h"


Vector::Vector():
    _capacity(0),
    _size(0),
    _multiplicativeCoef(2.0),
    _data(nullptr)
{
    newCapacity(1);
}

Vector::Vector(const Value *rawArray, const size_t size, float coef):
    Vector()
{
    _multiplicativeCoef = coef;
    newSize(size);
    for (size_t i = 0; i < _size; i++) {
        _data[i] = rawArray[i];
    }
}

Vector::Vector(const Vector &other) {
    _multiplicativeCoef = other._multiplicativeCoef;
    newCapacity(other._capacity);
    insert(other._data, other.size(), 0);
}

Vector &Vector::operator=(const Vector &other) {
    if (&other == this) {
        return *this;
    }
    Vector buff (other);
    std::swap(*this, buff);
    return *this;
}

Vector::Vector(Vector &&other) noexcept {
    _capacity = other._capacity;
    _size = other._size;
    _data = other._data;
    _multiplicativeCoef = other._multiplicativeCoef;
    other._data = nullptr;
    other._capacity = 0;
    other._size = 0;
}

Vector &Vector::operator=(Vector &&other) noexcept {
    if (&other == this) {
        return *this;
    }
    Vector buff (std::move(other));
    std::swap(*this, buff);
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

void Vector::popBack() {
    erase(_size - 1);
}

void Vector::popFront() {
    erase(0);
}

void Vector::erase(size_t pos, size_t count) {
    closeGap(pos, count);
}

void Vector::eraseBetween(size_t beginPos, size_t endPos) {
    erase(beginPos, endPos - beginPos + 1);
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

long long Vector::find(const Value& value) const {
    for (long long idx = 0; idx < _size; idx++) {
        if (_data[idx] == value) {
            return idx;
        }
    }
    return -1;
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
    if (newCapacity < _size) {
        newCapacity = _size;
    }
    Value* newData = new Value[newCapacity];
    _capacity = newCapacity;
    if (_data != nullptr) {
        for (size_t i = 0; i < _size; i++) {
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

void Vector::closeGap(size_t pos, size_t len) {
    if (len == 0) {
        return;
    }
    if (pos + len >= _size) {
        len = _size - pos;
    }
    for (size_t i = pos + len; i < _size; i++) {
        _data[i - len] = _data[i];
    }
    newSize(_size - len);
}
