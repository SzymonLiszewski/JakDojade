#include "queue.h"


template <typename T>
void Queue<T>::push(T const& elem) {
    // dodaje element na koniec wektora
    elements.push_back(elem);
}

template <typename T>
void Queue<T>::pop() {
    if (elements.empty()) {
        throw std::out_of_range("Queue<>::pop(): empty queue");
    }
    // usuwa pierwszy element z kolejki
    elements.erase(0);
}

template <typename T>
T Queue<T>::front() const {
    if (elements.empty()) {
        throw std::out_of_range("Queue<>::front(): empty queue");
    }
    // zwraca pierwszy element kolejki
    return elements.front();
}