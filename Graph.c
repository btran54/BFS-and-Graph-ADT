/***
* Brian Tran
* btran54
* 2024 Winter CSE101 PA2
* Graph.c
* Graph file containing the operations of Graph functions.
***/ 

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct GraphObj {
    List* neighbor;
    int* color;
    int* parent;
    int* dist;
    int order;
    int size;
    int source;
} GraphObj;

typedef struct GraphObj* Graoh;

// Constructors - Destructors ----------------------------------------------------
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));

    G->neighbor = calloc(n + 1, sizeof(List));
    G->color = calloc(n + 1, sizeof(int));
    G->parent = calloc(n + 1, sizeof(int));
    G->dist = calloc(n + 1, sizeof(int));
    G->order = n;
    G->size = 0;
    G->source = NIL;

    for (int i = 1; i <= n; i++) {
        G->neighbor[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->dist[i] = INF;
    }

    return G;
}

void freeGraph(Graph* pG) {
    Graph ptr = *pG;

    for (int i = 1; i <= getOrder(ptr); i++) {
        freeList(&(ptr->neighbor[i]));
    }

    free(ptr->neighbor);
    free(ptr->color);
    free(ptr->parent);
    free(ptr->dist);
    free(*pG);
}

int getOrder(Graph G) {
    if (G == NULL) {
        printf("Graph Error: Calling getOrder() on NULL graph reference.\n");
        exit(1);
    }

    return G->order;
}

int getSource(Graph G) {
    if (G == NULL) {
        printf("Graph Error: Calling getSource() on NULL graph reference.\n");
        exit(1);
    }

    return G->source;
}

int getSize(Graph G) {
    if (G == NULL) {
        printf("Graph Error: Calling getSize() on NULL graph reference.\n");
        exit(1);
    }

    return G->size;
}

int getParent(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: Calling getParent() on NULL graph reference.\n");
        exit(1);
    }

    if (!(1 <= u && u <= getOrder(G))) {
        printf("Graph Error: Cannot call getParent(). u is out of bounds.\n");
        exit(1);
    }

    return G->parent[u];
}

int getDist(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: Calling getDist() on NULL graph reference.\n");
        exit(1);
    }

    if (!(1 <= u && u <= getOrder(G))) {
        printf("Graph Error: Cannot call getDist(). u is out of bounds.\n");
        exit(1);
    }

    if(getSource(G) == NIL) {
        return INF;
    }
    
    return G->dist[u];
}

void getPath(List L, Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: Calling getPath() on NULL graph reference.\n");
        exit(1);
    }

    if (!(1 <= u && u <= getOrder(G))) {
        printf("Graph Error: Cannot call getPath(). u is out of bounds.\n");
        exit(1);
    }

    if (u == getSource(G)) {
        append(L, getSource(G));
    }

    else if (G->parent[u] == NIL) {
        append(L, NIL);
    }

    else {
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
}

// Manipulation Procedures -------------------------------------------------------
void makeNULL(Graph G) {
    if (G == NULL) {
        printf("Graph Error: Calling makeNULL() on NULL graph reference.\n");
        exit(1);
    }

    for (int i = 1; i <= getOrder(G); i++) {
        clear(G->neighbor[i]);
    }

    G->size = 0;
}

void sortedEdge(List L, int v) {
    if (L == NULL) {
        printf("List Error: Calling sorted edge on NULL list reference.\n");
        exit(1);
    }

    if (length(L) == 0) {
        append(L, v);
        return;
    }
    moveFront(L);

    while (index(L) != -1) {

        if (v < get(L)) {
            insertBefore(L, v);
            break;
        }
        moveNext(L);
    }

    if (index(L) == -1) {
        append(L, v);
    }
}

void addEdge(Graph G, int u, int v) {
    if (G == NULL) {
        printf("Graph Error: Calling addEdge() on NULL graph reference.\n");
        exit(1);
    }

    sortedEdge(G->neighbor[u], v);
    sortedEdge(G->neighbor[v], u);
    G->size++;
}

void addArc (Graph G, int u, int v) {
    if (G == NULL) {
        printf("Graph Error: Calling addArc() on NULL graph reference.\n");
        exit(1);
    }

    sortedEdge(G->neighbor[u], v);
    G->size++;
}

void BFS(Graph G, int s) {
    for (int x = 1; x <= getOrder(G); x++) {
        G->color[x] = WHITE;
        G->dist[x] = 0;
        G->parent[x] = NIL;
    }

    G->source = s;
    G->color[s] = GRAY;
    G->dist[s] = 0;
    G->parent[s] = NIL;
    List L = newList();
    append(L, s);

    while (length(L) > 0) {
        int x = front(L);
        deleteFront(L);
        List getNeighbor = G->neighbor[x];
        moveFront(getNeighbor);

        while (index(getNeighbor) != -1) {
            int y = get(getNeighbor);

            if (G->color[y] == WHITE) {
                G->color[y] = GRAY;
                G->dist[y] = G->dist[x] + 1;
                G->parent[y] = x;
                append(L, y);
            }
            
            moveNext(getNeighbor);
        }

        G->color[x] = BLACK;
    }

    freeList(&L);
}

void printGraph(FILE* out, Graph G) {
    if (G == NULL) {
        printf("Graph Error: Calling printGraph() on NULL graph reference.\n");
        exit(1);
    }

    for (int i = 1; i <= getOrder(G); i++) {
        List list = G->neighbor[i];
        fprintf(out, "%d: ", i);
        moveFront(list);

        while (index(list) != -1) {
            fprintf(out, "%d ", get(list));
            moveNext(list);
        }

        fprintf(out, "\n");
    }
}