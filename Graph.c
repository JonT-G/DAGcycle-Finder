#include <stdio.h>  
#include <stdlib.h>
#include "Graph.h"
#include "LinkedList.h"

Graph *Graph_new(int n) {
    // Allocate memory for the Graph
    Graph *g = (Graph *)malloc(sizeof(Graph));
    if (!g) return NULL; 

    (*g).numVertices = n;
    (*g).numEdges = 0;

    // Allocate memory for the vertices array
    Vertex *vertices = (Vertex *)malloc(n * sizeof(Vertex));
    if (!vertices) {
        free(g); 
        return NULL;
    }
    (*g).vertices = vertices;

    // Initialize each vertex
    for (int i = 0; i < n; i++) {
        vertices[i].id = i; 
        vertices[i].outNeighbours = LinkedList_new(); 
        vertices[i].inNeighbours = LinkedList_new();  
    }

    return g; 
}



void Graph_delete(Graph *g) {
    if (!g) return;

    Vertex *vertices = (*g).vertices;
    int numVertices = (*g).numVertices; 

    // Free linked lists for each vertex
    for (int i = 0; i < numVertices; i++) {
        LinkedList_delete(vertices[i].outNeighbours);
        LinkedList_delete(vertices[i].inNeighbours);
    }

    // Free memory of the vertices array
    free(vertices);

    // Free memory of the graph structure
    free(g);
}



void Graph_addEdge(Graph *g, int i, int j) {
    // Part to make sure the graph is a valid graph before doing anything
    if (!g) {
        return; 
    }

    Vertex *vertices = (*g).vertices;
    int numVertices = (*g).numVertices;

    if (i < 0 || i >= numVertices) {
        return; 
    }

    if (j < 0 || j >= numVertices) {
        return; 
    }

    // adding edge to the graph structure
    LinkedList_append(vertices[i].outNeighbours, &vertices[j]);
    LinkedList_append(vertices[j].inNeighbours, &vertices[i]);

    // update the numegdes int so we know number of egdes in the graph
    (*g).numEdges++;
}

Graph *Graph_read(const char *filename) {
    // open the file and check for error
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }

    // Read the number of vertices the graph in the file has 
    int numVertices;
    if (fscanf(file, "%d", &numVertices) != 1) {
        printf("Error: Could not read number of vertices.\n");
        fclose(file);
        return NULL;
    }

    // Create a new graph
    Graph *g = Graph_new(numVertices);
    if (!g) {
        printf("Error: Could not create graph.\n");
        fclose(file);
        return NULL;
    }

    // Read the adjacency matrix and create the edges
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            int edge;
            if (fscanf(file, "%1d", &edge) != 1) {
                printf("Error: Could not read adjacency matrix.\n");
                Graph_delete(g);
                fclose(file);
                return NULL;
            }
            if (edge == 1) {
                Graph_addEdge(g, i, j);
            }
        }
    }

    fclose(file);
    return g;
}



void Graph_print(Graph *g) {
    if (!g) {
        printf("Graph is NULL.\n");
        return;
    }

    printf("Graph:\n");
    printf("Number of vertices: %d\n", (*g).numVertices);
    printf("Number of edges: %d\n", (*g).numEdges);

    // Print adjacency list representation
    for (int i = 0; i < (*g).numVertices; i++) {
        printf("Vertex %d: ", (*g).vertices[i].id);
        LinkedList *outNeighbours = (*g).vertices[i].outNeighbours;
        LinkedListNode *node = (*outNeighbours).head;

        while (node) {
            Vertex *neighbor = (Vertex *)(*node).data;
            printf("%d -> ", (*neighbor).id);
            node = (*node).next;
        }
        printf("NULL\n");
    }
}
