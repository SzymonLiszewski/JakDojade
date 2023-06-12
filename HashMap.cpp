#include "HashMap.h"
#include <stdexcept>


HashMap::HashMap(int capacity) {
    this->capacity = capacity;
    table = new Node * [capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
}

HashMap::~HashMap() {
    for (int i = 0; i < capacity; i++) {
        Node* current = table[i];
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    delete[] table;
}

void HashMap::put(MyString key, int value) {
    int index = hash(key);
    Node* current = table[index];
    while (current != nullptr) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }
    Node* newNode = new Node;
    newNode->key = key;
    newNode->value = value;
    newNode->next = table[index];
    table[index] = newNode;
}

int HashMap::get(MyString key) {
    int index = hash(key);
    Node* current = table[index];
    while (current != nullptr) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

void HashMap::remove(MyString key) {
    int index = hash(key);
    Node* current = table[index];
    Node* previous = nullptr;
    while (current != nullptr) {
        if (current->key == key) {
            if (previous == nullptr) {
                table[index] = current->next;
            }
            else {
                previous->next = current->next;
            }
            delete current;
            return;
        }
        previous = current;
        current = current->next;
    }
}

bool HashMap::contains(MyString key) {
    int index = hash(key);
    Node* current = table[index];
    while (current != nullptr) {
        if (current->key == key) {
            return true;
        }
        current = current->next;
    }
    return false;
}

constexpr size_t FNV_PRIME = 1099511628211;
constexpr size_t FNV_OFFSET_BASIS = 14695981039346656037ULL;

int HashMap::hash(MyString key) {
    const float phi = 1.61803398875;
    int hashValue = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hashValue = phi * hashValue + key[i];
    }
    return hashValue % capacity;
}