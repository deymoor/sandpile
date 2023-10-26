#pragma once
#include <cstdint>
#include <cstddef>

template <typename T> struct Vector{
    T* array;
    uint64_t capacity;
    uint64_t current;

    Vector() {
        array = new T[1];
        capacity = 1;
        current = 0;
    }

    ~Vector() {
        delete[] array;
    }

    void push_back(T data) {
        if (current == capacity) {
            T* temp = new T[2 * capacity];
            for (size_t i = 0; i < capacity; ++i) {
                temp[i] = array[i];
            }
            delete[] array;
            capacity *= 2;
            array = temp;
        }
        array[current] = data;
        current++;
    }

    void pop_back() {
        current--;
    }

    uint64_t size() {
        return current;
    }

    T& operator[] (size_t index) {
        return array[index];
    }
};
