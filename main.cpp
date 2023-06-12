#include "mystring.cpp"
#include "graph.h"
#include <iostream>
#include "stack.cpp"
#include "vector.cpp"
#include "queue.cpp"
#include "HashMap.h"
#define ID 128



void getName(MyString* str, int** t, int i, int j, int size_x) {
    if ((char)t[i][j] != '*' && (char)t[i][j] != '.' && (char)t[i][j] != '#') {
        while ((char)t[i][j] != '*' && (char)t[i][j] != '.' && (char)t[i][j] != '#' && j >= 0) { j--; }
        j++;
        while ((char)t[i][j] != '*' && (char)t[i][j] != '.' && (char)t[i][j] != '#' && j < size_x) {
            str->addchar((char)t[i][j]);
            j++;
        }
    }
}

MyString findName(int** t, int i, int j, int size_x, int size_y) {
    MyString str = "";
    if (j + 1 < size_x) { getName(&str, t, i, j + 1, size_x); if (!(str == "")) { return str; } }
    if (j + 1 < size_x && i + 1 < size_y) { getName(&str, t, i + 1, j + 1, size_x); if (!(str == "")) { return str; } }
    if (i + 1 < size_y) { getName(&str, t, i + 1, j, size_x); if (!(str == "")) { return str; } }
    if (i + 1 < size_y && j - 1 >= 0) { getName(&str, t, i + 1, j - 1, size_x); if (!(str == "")) { return str; } }
    if (j - 1 >= 0) { getName(&str, t, i, j - 1, size_x); if (!(str == "")) { return str; } }
    if (i - 1 >= 0 && j - 1 >= 0) { getName(&str, t, i - 1, j - 1, size_x); if (!(str == "")) { return str; } }
    if (i - 1 >= 0) { getName(&str, t, i - 1, j, size_x); if (!(str == "")) { return str; } }
    if (i - 1 >= 0 && j + 1 < size_x) { getName(&str, t, i - 1, j + 1, size_x); if (!(str == "")) { return str; } }
    return str;
}

struct path {
    int i;
    int j;
    int distance;
};

bool isValid(int** visited, int row, int col, int i, int j) {
    if (i < 0 || j < 0 || i >= row || j >= col) {
        return false;
    }
    if (visited[i][j] == 1) {
        return false;
    }
    return true;
};

void DFS(int row, int col, int** tab, struct Graph** graph, int start_x, int start_y) {
    int dRow[] = { 0, 1, 0, -1 };
    int dCol[] = { -1, 0, 1, 0 };
    int** visited = new int* [row];
    for (int i = 0; i < row; i++) {
        visited[i] = new int[col];
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            visited[i][j] = 0;
        }
    }
    StackNode<path>* root = NULL;
    struct path p1 = { start_x,start_y,0 };
    push<path>(&root, p1);

    while (!(isEmpty<path>(root))) {
        struct path current = pop<path>(&root);
        int i = current.i;
        int j = current.j;

        /*if (!isValid(visited, row, col, i, j)) {
                continue;
        }*/
        visited[i][j] = 1;
        int distance = current.distance + 1;
        struct path temp;
        for (int k = 0; k < 4; k++) {
            int adjx = i + dRow[k];
            int adjy = j + dCol[k];
            struct path p1 = { adjx, adjy, distance };
            if (!(isEmpty(root))) { temp = peek<path>(root); }
            if (isValid(visited, row, col, adjx, adjy)) {
                if ((char)tab[adjx][adjy] == '#') {
                    p1 = { adjx, adjy, distance };
                    push<path>(&root, p1);
                }
                else if (tab[adjx][adjy] >= ID) {
                    struct node* templist = (*graph)->array[tab[start_x][start_y] - ID].head;
                    int isinlist = 0;
                    while (templist != nullptr && templist->next != NULL) {
                        if (templist->dest == tab[adjx][adjy] - ID) {
                            isinlist = 1;
                            if (templist->distance > distance) {
                                templist->distance = distance;
                                break;
                            }
                        }
                        templist = templist->next;
                    }
                    if (isinlist == 0) {
                        addEdge(*graph, tab[start_x][start_y] - ID, tab[adjx][adjy] - ID, distance);
                    }
                }
            }
        }
        //distance++;
    }
}
void BFS(int row, int col, int** tab, struct Graph** graph, int start_x, int start_y, int** visited) {
    int dRow[] = { -1, 0, 1, 0 };
    int dCol[] = { 0, 1, 0, -1 };
    Queue<path> q;

    q.push({ start_x, start_y, 0 });

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            visited[i][j] = 0;
        }
    }

    int distance = 0;
    while (!q.empty()) {

        path cell = q.front();
        int x = cell.i;
        int y = cell.j;


        q.pop();
        int distance = cell.distance + 1;

        for (int i = 0; i < 4; i++) {

            int adjx = x + dRow[i];
            int adjy = y + dCol[i];

            if (isValid(visited, row, col, adjx, adjy)) {
                visited[adjx][adjy] = 1;
                if ((char)tab[adjx][adjy] == '#') {
                    q.push({ adjx, adjy, distance });
                }
                else if (tab[adjx][adjy] >= ID) {
                    struct node* templist = (*graph)->array[tab[start_x][start_y] - ID].head;
                    int isinlist = 0;
                    while (templist != nullptr && templist->next != NULL) {
                        if (templist->dest == tab[adjx][adjy] - ID) {
                            isinlist = 1;
                            if (templist->distance > distance) {
                                templist->distance = distance;
                                break;
                            }
                        }
                        templist = templist->next;
                    }
                    if (isinlist == 0) {
                        addEdge(*graph, tab[start_x][start_y] - ID, tab[adjx][adjy] - ID, distance);
                    }
                }
            }
        }
    }
}

typedef struct MinHeapNode MinHeapNode;

struct MinHeapNode {
    int v;
    int dist;
};

typedef struct MinHeap MinHeap;

struct MinHeap {
    int size;
    int capacity;
    int* pos;
    MinHeapNode** array;
};

MinHeapNode* newMinHeapNode(int v, int dist) {
    MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx, left = 2 * idx + 1, right = 2 * idx + 2;
    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;
    if (smallest != idx) {
        MinHeapNode* smallestNode = minHeap->array[smallest], * idxNode = minHeap->array[idx];
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}

MinHeapNode* extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap))
        return NULL;
    MinHeapNode* root = minHeap->array[0], * lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;
    --minHeap->size;
    minHeapify(minHeap, 0);
    return root;
}

void decreaseKey(MinHeap* minHeap, int v, int dist) {
    int i = minHeap->pos[v];
    minHeap->array[i]->dist = dist;
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
bool isInMinHeap(struct MinHeap* minHeap, int v)
{
    return (minHeap->pos[v] < minHeap->size);
}

void printArr(int dist[], int src, int dest, int* prev, int V, MyString* cities_names, int option)
{
    std::cout << "distance between " << cities_names[src]<<" and "<<cities_names[dest]<<": "<<dist[dest]<<"\n";
    int counter = 0;
    if (option == 1) {
        StackNode<int>* path;
        int curr = dest;
        while (curr != src) {
            push(&path, curr);
            counter++;
            curr = prev[curr];
        }
        //push(&path, src);
        //counter++;
        while (counter > 1) {
            int v = pop(&path);
            std::cout << "through cities: " << cities_names[v];
            counter--;
        }
    }
    printf("\n");
    /*printf("%d", dist[dest]);
    StackNode<MyString>* root;
    int count = 0;
    if (option == 1){
            for (int i = 0; i < V; i++) {
                    if (visited_cities[i][dest] == 1 && i!=src) {
                            push<MyString>(&root, cities_names[i]);
                            //std::cout << cities_names[i]<<" ";
                            dest = i;
                            i = 0;
                            count++;
                    }
            }
    }
    for (int i = 0; i < count; i++) {
            MyString str = pop<MyString>(&root);
            std::cout << " " << str;
    }
    printf("\n");*/
}

void dijkstra(struct Graph* graph, int src, int dest, MyString* cities_names, int option)
{
    int V = graph->V;
    int* dist = new int[V];
    int* prev = new int[V];

    struct MinHeap* minHeap = createMinHeap(V);
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
        prev[v] = -1;
    }

    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
    minHeap->size = V;

    while (!isEmpty(minHeap))
    {
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;

        struct node* pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->distance + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->distance;
                prev[v] = u;
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
    printArr(dist, src, dest, prev, V, cities_names, option);
    delete[] prev;
    delete[]dist;
}

int main() {
    int m, n, id = 0;
    std::cin >> n >> m;
    int** tab = new int* [m];
    for (int i = 0; i < m; i++) {
        tab[i] = new int[n];
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            tab[i][j] = getchar();
            while (tab[i][j] == '\n') { tab[i][j] = getchar(); }
            if ((char)tab[i][j] == '*') {
                id++;
            }
        }
    }
    struct Graph* graph = createGraph(id);//id+1?
    MyString* cities_names = new MyString[id];
    for (int i = 0; i < id; i++) {
        cities_names[i] = "";
    }
    id = 0;
    HashMap cities_hash;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if ((char)tab[i][j] == '*') {
                MyString s = findName(tab, i, j, n, m);
                cities_names[id].add(s);
                cities_hash.put(s, id);
                tab[i][j] = id + ID;
                id++;
            }
        }
    }
    int flights_number;
    std::cin >> flights_number;
    for (int i = 0; i < flights_number; i++) {
        int src_city_id, dest_city_id, distance;
        MyString src_city, dest_city;
        char a = getchar();
        while (a == ' ' || a == '\n') { a = getchar(); }
        while (a != ' ' && a != '\n') {
            src_city.addchar(a);
            a = getchar();
        }
        while (a == ' ' || a == '\n') { a = getchar(); }
        while (a != ' ' && a != '\n') {
            dest_city.addchar(a);
            a = getchar();
        }
        std::cin >> distance;
        src_city_id = cities_hash.get(src_city);
        dest_city_id = cities_hash.get(dest_city);
        addEdge(graph, src_city_id, dest_city_id, distance);
    }
    //addEdge(graph, 0, 1, 10);
    int** visited = new int* [m];
    for (int i = 0; i < m; i++) {
        visited[i] = new int[n];
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (tab[i][j] >= ID) {
                BFS(m, n, tab, &graph, i, j, visited);
            }
        }
    }
    for (int i = 0; i < m; i++) {
        delete visited[i];
    }
    delete[] visited;
    int search_number;
    std::cin >> search_number;
    for (int i = 0; i < search_number; i++) {
        int src_city_id, dest_city_id, option;
        MyString src_city, dest_city;
        char a = getchar();
        while (a == ' ' || a == '\n') { a = getchar(); }
        while (a != ' ' && a != '\n') {
            src_city.addchar(a);
            a = getchar();
        }
        while (a == ' ' || a == '\n') { a = getchar(); }
        while (a != ' ' && a != '\n') {
            dest_city.addchar(a);
            a = getchar();
        }
        std::cin >> option;
        src_city_id = cities_hash.get(src_city);
        dest_city_id = cities_hash.get(dest_city);
        dijkstra(graph, src_city_id, dest_city_id, cities_names, option);
    }

    //std::cout << graph->array[0].head->dest;
    //std::cout << graph->array[0].head->distance;

    /*
    //test wypisywania
    std::cout << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                    std::cout << (char)tab[i][j];
            }
            std::cout << std::endl;
    }//*/

    for (int i = 0; i < m; i++) {
        delete tab[i];
    }
    delete[] tab;
    delete[] cities_names;
}