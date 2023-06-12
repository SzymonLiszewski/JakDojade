//#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma once
#include <iostream>
#include <string.h>

#define N 15

class MyString {
private:
    char* data;
    size_t size;
    size_t tabSize;
public:
    MyString(size_t s) {
        this->data = new char[s];
        this->size = s;
        this->tabSize = s;

        if (this->data != NULL) {
            for (size_t i = 0; i < s; i++) {
                data[i] = '\0';
            }
        }
    }
    MyString() {
        size_t s = N;
        this->data = new char[s];
        this->size = 0;
        this->tabSize = s;

        if (this->data != NULL) {
            for (size_t i = 0; i < s; i++) {
                data[i] = '\0';
            }
        }
    }
    ~MyString() {
        if (this->data != NULL) {
            delete[] this->data;
        }
    }
    MyString(const char* data) {
        //delete[] this->data;
        size_t s = strlen(data);
        this->tabSize = s + N;
        this->data = new char[this->tabSize];
        this->size = s;

        if (this->data != NULL) {
            strncpy(this->data, data, s);
            //std::cout << s;
        }
        this->data[size] = '\0';
    }
    MyString(const MyString& string) {
        this->size = string.size;
        this->tabSize = string.size + N;
        this->data = new char[this->tabSize];

        if (this->data != NULL) {
            strncpy(this->data, string.data, this->size);
        }
        this->data[size] = '\0';
    }
    friend std::ostream& operator<<(std::ostream& os, const MyString& string) {
        for (size_t i = 0; i < string.size; i++) {
            std::cout << string.data[i];
        }
        return os;
    }
    char operator[](size_t index) {
        return data[index];
    }
    MyString& operator=(const MyString& string1) {
        this->clear();
        this->add(string1);
        return *this;
    }
    bool compare(const MyString& string) const {
        return strcmp(this->data, string.data) == 0;
    }
    friend bool operator==(const MyString& string1, const MyString& string2) {
        return string1.compare(string2);
    }
    friend std::istream& operator>>(std::istream& is, MyString& string) {
        //string.setSize(N);
        is >> string.data;
        return is;
    }
    /*MyString operator=(MyString string2) {
            if (this->data != NULL) {
                    strncpy(this->data, string2.data, this->size);
            }
            return string2;
    }*/
    void setSize(size_t size) {
        size_t old_size = this->getSize();
        char* old_data = this->data;

        //this->size = size;
        this->tabSize = size + N;
        this->data = new char[this->tabSize];

        for (size_t i = 0; i < size; i++) {
            if (i < old_size) {
                this->data[i] = old_data[i];
            }
            else {
                this->data[i] = '\0';
            }
        }
        //delete[] old_data;
    }

    size_t getSize() const {
        return strlen(this->data);
    }
    void add(const MyString& string) {
        size_t new_size = this->size + string.size;
        size_t length = this->size;
        //std::cout << length << std::endl;
        this->size = new_size;
        if (new_size > this->tabSize) {
            setSize(new_size);
            //std::cout << "powiekszenie tab";
        }

        for (size_t i = length; i < new_size; i++) {
            this->data[i] = string.data[i - length];
            //std::cout << i<<string.data[i - length];
        }
        this->data[size] = '\0';
    }
    void addchar(char c) {
        if (this->size >= this->tabSize - 1) {
            size_t s = this->size + N;
            //std::cout << "powiekszenie tab";
            setSize(s);
        }
        this->data[size] = c;
        this->data[size + 1] = '\0';
        this->size++;
        //std::cout << this->size<<" "<<this->tabSize<<std::endl;
    }
    void removeLast() {
        this->data[size - 1] = '\0';
        this->size--;
        //std::cout << this->size<<" "<<this->tabSize<<std::endl;
    }
    size_t getTabsize() const {
        return this->tabSize;
    }
    size_t getSize() {
        return this->size;
    }
    int stoi() {
        int output = 0;
        for (int i = 1; i <= this->size; i++) {
            output += (this->data[this->size - i] - 48) * pow(10, i - 1);
        }
        return output;
    }
    void clear() {
        this->size = 0;
    }
};