#pragma once
#include "vector.h"

template <typename T>
class Queue {
private:
    Vector<T> elements;
public:
    void push(T const&);
    void pop();
    T front() const;
    bool empty() const {
        return elements.empty();
    }
};