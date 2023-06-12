#include "vector.h"

template <typename T>
Vector<T>::Vector(std::size_t const& n) : elements(new T[n]), capacity(n), size(0) {}

template <typename T>
Vector<T>::Vector(Vector const& other) : elements(new T[other.capacity]), capacity(other.capacity), size(other.size) {
    // kopiujemy elementy z innego wektora
    for (std::size_t i = 0; i < size; ++i) {
        elements[i] = other.elements[i];
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector const& other) {
    if (this != &other) {
        delete[] elements;
        elements = new T[other.capacity];
        capacity = other.capacity;
        size = other.size;
        // kopiujemy elementy z innego wektora
        for (std::size_t i = 0; i < size; ++i) {
            elements[i] = other.elements[i];
        }
    }
    return *this;
}

template <typename T>
Vector<T>::~Vector() {
    delete[] elements;
}

template <typename T>
void Vector<T>::push_back(T const& elem) {
    if (size == capacity) {
        // alokujemy nową tablicę o podwójnej pojemności
        capacity = capacity == 0 ? 1 : capacity * 2;
        T* new_elements = new T[capacity];
        // kopiujemy elementy do nowej tablicy
        for (std::size_t i = 0; i < size; ++i) {
            new_elements[i] = elements[i];
        }
        // usuwamy starą tablicę
        delete[] elements;
        // przypisujemy nową tablicę do wektora
        elements = new_elements;
    }
    // dodajemy element na koniec wektora
    elements[size] = elem;
    ++size;
}
template <typename T>
void Vector<T>::pop_back() {
    if (size > 0) {
        --size;
    }
}

template <typename T>
T& Vector<T>::operator[](std::size_t const& index) {
    return elements[index];
}

template <typename T>
T const& Vector<T>::operator[](std::size_t const& index) const {
    return elements[index];
}

template <typename T>
std::size_t Vector<T>::getsize() const {
    return size;
}

template <typename T>
std::size_t Vector<T>::getcapacity() const {
    return capacity;
}

template <typename T>
bool Vector<T>::empty() const {
    return size == 0;
}
template <typename T>
void Vector<T>::erase(std::size_t index) {
    if (index < size) {
        for (std::size_t i = index; i < size - 1; i++) {
            elements[i] = elements[i + 1];
        }
        size--;
    }
}
template <typename T>
T* Vector<T>::begin() const {
    return elements;
}
template <typename T>
T& Vector<T>::front() const {
    return elements[0];
}