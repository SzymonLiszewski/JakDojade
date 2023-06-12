#pragma once
#include "mystring.cpp"
#include "graph.h"


struct node* newAdjListNode(int dest, int distance) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->dest = dest;
    newNode->distance = distance;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int Vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = Vertices;
    graph->array = (struct adjList*)malloc(Vertices * sizeof(struct adjList));
    MyString s("lol");
    for (int i = 0; i < Vertices; i++) {
        graph->array[i].head = NULL;
        //graph->array[i].name = s;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int distance) {
    struct node* newNode = newAdjListNode(dest, distance);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

void addName(struct Graph* graph, MyString name, int id) {
    int xd = 0;
    //graph->array[id].name = name;
}