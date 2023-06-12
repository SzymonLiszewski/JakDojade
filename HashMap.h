#include <iostream>
#include "mystring.cpp"

class HashMap {
public:
    HashMap(int capacity = 5000);
    ~HashMap();
    void put(MyString key, int value);
    int get(MyString key);
    void remove(MyString key);
    bool contains(MyString key);

private:
    struct Node {
        MyString key;
        int value;
        Node* next;
    };

    Node** table;
    int capacity;

    int hash(MyString key);
};