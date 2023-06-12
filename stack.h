#pragma once

template <typename T> class StackNode
{
public:
    T data;
    StackNode* next;
    //int size;
    //StackNode();
};
template <typename T> StackNode<T>* newNode();
template <typename T> StackNode<T>* newNode(T data);
template <typename T> int isEmpty(StackNode<T>* root);
template <typename T> void push(StackNode<T>** root, T data);
template <typename T> T pop(StackNode<T>** root);
template <typename T> T peek(StackNode<T>* root);