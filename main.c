#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "cycleDetection.h"

int main(int argc, char *argv[]) {
    // Need a filepath to read from
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1]; // File path as argument

    // Read the graph from the file given
    Graph *g = Graph_read(filename);
    if (!g) {
        printf("Error: Could not read graph from file %s.\n", filename);
        return 1;
    }

    cycleDetection(g);
    Graph_delete(g);
    return 0;
}

