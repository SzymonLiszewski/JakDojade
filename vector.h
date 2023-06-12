#pragma once
#include <iostream>

template <typename T>
class Vector {
private:
    T* elements;
    std::size_t capacity;
    std::size_t size;
public:
    Vector() : elements(nullptr), capacity(0), size(0) {}
    explicit Vector(std::size_t const&);
    Vector(Vector const&);
    Vector& operator=(Vector const&);
    ~Vector();
    void push_back(T const&);
    void pop_back();
    T& operator[](std::size_t const&);
    T const& operator[](std::size_t const&) const;
    std::size_t getsize() const;
    std::size_t getcapacity() const;
    bool empty() const;
    void erase(std::size_t index);
    T* begin() const;
    T& front() const;
};