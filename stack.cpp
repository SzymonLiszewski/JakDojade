#pragma once
#include "stack.h"
#include <stdexcept>

/*template <typename T> StackNode<T>::StackNode() {
        data = NULL;
}*/

template <typename T> StackNode<T>* newNode() {
    StackNode<T>* stackNode = new StackNode<T>();
    stackNode->data = NULL;
    stackNode->next = nullptr;
    //stackNode->size = 0;
    return stackNode;
}
template <typename T> StackNode<T>* newNode(T data) {
    StackNode<T>* stackNode = new StackNode<T>();
    stackNode->data = data;
    stackNode->next = nullptr;
    //stackNode->size = 1;
    return stackNode;
}
template <typename T> int isEmpty(StackNode<T>* root) {
    return !root;
}

template <typename T> void push(StackNode<T>** root, T data) {
    StackNode<T>* stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
    //(*root)->size += 1;
}

template <typename T> T pop(StackNode<T>** root) {
    if (!(isEmpty(*root))) {
        StackNode<T>* temp = *root;
        *root = (*root)->next;
        T popped = temp->data;
        free(temp);
        //(*root)->size -= 1;
        return popped;
    }
    throw std::out_of_range("Stack<>::pop(): empty stack");
}

template <typename T> T peek(StackNode<T>* root) {
    if (!(isEmpty(root))) {
        return root->data;
    }
    throw std::out_of_range("Stack<>::peek(): empty stack");
}