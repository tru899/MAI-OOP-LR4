#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>
using namespace std;

template <typename T>
class Array {
private:
    size_t count;
    size_t max_capacity;
    unique_ptr<T[]> data;
    void increase_capacity(size_t new_cap) {
        auto new_data = make_unique<T[]>(new_cap);
        for (size_t i = 0; i < count; ++i) new_data[i] = move(data[i]);
        data = move(new_data);
        max_capacity = new_cap;
    }
public:
    Array() : count(0), max_capacity(10), data(make_unique<T[]>(10)) {}
    Array(initializer_list<T> items) {
        count = items.size();
        max_capacity = count * 2;
        data = make_unique<T[]>(max_capacity);
        size_t i = 0;
        for (auto& e : items) data[i++] = e;
    }
    Array(const Array& other) {
        count = other.count;
        max_capacity = other.max_capacity;
        data = make_unique<T[]>(max_capacity);
        for (size_t i = 0; i < count; ++i) data[i] = other.data[i];
    }
    Array(Array&& other) noexcept {
        count = other.count;
        max_capacity = other.max_capacity;
        data = move(other.data);
        other.count = 0;
        other.max_capacity = 0;
    }
    Array& operator=(const Array& other) {
        if (this != &other) {
            count = other.count;
            max_capacity = other.max_capacity;
            data = make_unique<T[]>(max_capacity);
            for (size_t i = 0; i < count; ++i) data[i] = other.data[i];
        }
        return *this;
    }
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            count = other.count;
            max_capacity = other.max_capacity;
            data = move(other.data);
            other.count = 0;
            other.max_capacity = 0;
        }
        return *this;
    }
    void add(const T& elem) {
        if (count >= max_capacity) increase_capacity(max_capacity * 2);
        data[count++] = elem;
    }
    void remove(size_t pos) {
        if (pos >= count) throw out_of_range("Index out of range");
        for (size_t i = pos; i < count - 1; ++i) data[i] = move(data[i + 1]);
        --count;
    }
    T& operator[](size_t pos) {
        if (pos >= count) throw out_of_range("Index out of range");
        return data[pos];
    }
    const T& operator[](size_t pos) const {
        if (pos >= count) throw out_of_range("Index out of range");
        return data[pos];
    }
    size_t size() const { return count; }
    size_t capacity() const { return max_capacity; }
};
