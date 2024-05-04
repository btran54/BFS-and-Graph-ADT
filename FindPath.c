/***
* Brian Tran
* btran54
* 2024 Winter CSE101 PA2
* FindPath.c
* FindPath file containing the main execution of functions from Graph.c
***/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Invalid Arguments.\nUsage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");

    if (in == NULL) {
        printf("Unable to open file %s for reading.\n", argv[1]);
        exit(1);
    }

    if (out == NULL) {
        printf("Unable to open %s for writing.\n", argv[2]);
        exit(1);
    }

    int n =0;
    fscanf(in, "%d", &n);
    Graph graph = newGraph(n);
    int tempSource = 0;
    int tempDest = 0;
    int src = 0;
    int dst = 0;

    /* 1. Read and store the graph and print out its adjacency list representation. */

    while (fgetc(in) != EOF) {
        fscanf(in, "%d", &tempSource);
        fscanf(in, "%d", &tempDest);

        if (tempSource == 0 && tempDest == 0) {
            break;
        }

        addEdge(graph, tempSource, tempDest);
    }

    printGraph(out, graph);
    fprintf(out, "\n");

    /* 2. Enter a loop that processes the second part of the input. Each iteration of the loop should read in one
        pair of vertices (source, destination), run BFS on the source vertex, print the distance to the destination
        vertex, then find and print the resulting shortest path, if it exists, or print a message that no path from
        source to destination exists (as in the above example). */
    
    while (fgetc(in) != EOF) {
        fscanf(in, "%d", &src);
        fscanf(in, "%d", &dst);

        if (src == 0 && dst == 0) {
            break;
        }

        List list = newList();
        BFS(graph, src);
        getPath(list, graph, dst);

        if (getDist(graph, dst) != INF) {
            fprintf(out, "The distance from %d to %d is %d\n", src, dst, length(list) - 1);
            fprintf(out, "A shortest %d-%d path is: ", src, dst);
            printList(out, list);
            fprintf(out, "\n\n");
        }

        else {
            fprintf(out, "The distance from %d to %d is infinity\n", src, dst);
            fprintf(out, "No %d-%d path exists\n\n", src, dst);
        }

        freeList(&list);
    }

    freeGraph(&graph);
    fclose(in);
    fclose(out);
    return 0;
}