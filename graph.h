#pragma once
#include "mystring.cpp"


struct node
{
    int dest;
    int distance;
    struct node* next;
};

struct adjList {
    //MyString name;
    struct node* head;
};

struct Graph {
    int V;
    struct adjList* array;
};
struct node* newAdjListNode(int dest, int distance);
struct Graph* createGraph(int Vertices);
void addEdge(struct Graph* graph, int src, int dest, int distance);
void addName(struct Graph* graph, MyString name, int id);