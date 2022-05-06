//
// Created by brinza on 11.03.2022.
//

#include <algorithm>
#include <stdexcept>

#include "Vector.h"


Vector::Vector(const Value *rawArray, const size_t size, float coef) {
    _multiplicativeCoef = coef;
    insert(rawArray, size, 0);
}

Vector::Vector(const Vector &other) {
    _multiplicativeCoef = other._multiplicativeCoef;
    insert(other, 0);
}

Vector &Vector::operator=(const Vector &other) {
    if (&other == this) {
        return *this;
    }
    _capacity = 0;
    _size = 0;
    delete[] _data;
    _data = nullptr;
    _multiplicativeCoef = other._multiplicativeCoef;
    insert(other, 0);
    return *this;
}

Vector::Vector(Vector &&other) noexcept {
    _data = other._data;
    _capacity = other._capacity;
    _size = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;
    other._data = nullptr;
    other._capacity = 0;
    other._size = 0;
}

Vector &Vector::operator=(Vector &&other) noexcept {
    if (&other == this) {
        return *this;
    }
    _capacity = other._capacity;
    _size = other._size;
    _data = other._data;
    _multiplicativeCoef = other._multiplicativeCoef;
    other._data = nullptr;
    other._capacity = 0;
    other._size = 0;
    return *this;
}

Vector::~Vector() {
    _capacity = 0;
    _size = 0;
    delete [] _data;
}

void Vector::pushBack(const Value &value) {
    insert(value, size());
}

void Vector::pushFront(const Value &value) {
    insert(value, 0);
}

void Vector::insert(const Value& value, size_t pos) {
    insert(&value, 1, pos);
}

void Vector::insert(const Value* values, size_t size, size_t pos) {
    if (_capacity < _size + size) {
        reserve((_size + size) * _multiplicativeCoef);
    }
    for (size_t idx = _size; idx > pos; idx--) {
        _data[idx - 1 + size] = _data[idx - 1];
    }
    for (size_t i = 0; i < size; i++) {
        _data[pos + i] = values[i];
    }
    _size += size;
}

void Vector::insert(const Vector& vector, size_t pos) {
    insert(vector._data, vector.size(), pos);
}

void Vector::popBack() {
    erase(_size - 1);
}

void Vector::popFront() {
    erase(0);
}

void Vector::erase(size_t pos, size_t count) {
    if (_size == 0) {
        throw std::length_error("Can't erase in empty vector");
    }
    if (pos + count >= _size) {
        count = _size - pos;
    }
    for (size_t idx = pos + count; idx < _size; idx++) {
        _data[idx - count] = _data[idx];
    }
    _size -= count;
}

void Vector::eraseBetween(size_t beginPos, size_t endPos) {
    erase(beginPos, endPos - beginPos);
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
    Value* newData = new Value[capacity];
    if (_data != nullptr) {
        for (size_t idx = 0; idx < _size; idx++) {
            newData[idx] = _data[idx];
        }
        delete _data;
    }
    _capacity = capacity;
    _data = newData;
}

void Vector::shrinkToFit() {
    if (_capacity == _size) {
        return;
    }
    Value* newData = new Value[_size];
    if (_data != nullptr) {
        for (size_t idx = 0; idx < _size; idx++) {
            newData[idx] = _data[idx];
        }
        delete _data;
    }
    _data = newData;
    _capacity = _size;
}

Vector::Iterator Vector::begin() {
    return Vector::Iterator(_data);
}

Vector::Iterator Vector::end() {
    return Vector::Iterator(_data + size());
}


// Iterator class

Vector::Iterator::Iterator(Value* ptr) : _ptr(ptr) {}


Value& Vector::Iterator::operator*() {
    return *_ptr;
}

const Value& Vector::Iterator::operator*() const {
    return *_ptr;
}

Value* Vector::Iterator::operator->() {
    return _ptr;
}

const Value* Vector::Iterator::operator->() const {
    return _ptr;
}

Vector::Iterator Vector::Iterator::operator++() {
    _ptr++;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) {
    Iterator tmp (*this);
    _ptr++;
    return tmp;
}

bool Vector::Iterator::operator==(const Vector::Iterator& other) const {
    return _ptr == other._ptr;
}

bool Vector::Iterator::operator!=(const Vector::Iterator& other) const {
    return !(*this == other);
}
