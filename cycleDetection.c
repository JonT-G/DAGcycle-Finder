#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "LinkedList.h"

void cycleDetection(Graph *g) {
    if (!g) {
        printf("Error: Graph is NULL.\n");
        return;
    }

    // Allocate memory for the in-degrees of all vertices
    int *inDegree = (int *)calloc((*g).numVertices, sizeof(int));
    if (!inDegree) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    // Calculate the in-degrees of each vertex
    Vertex *vertices = (*g).vertices;
    for (int i = 0; i < (*g).numVertices; i++) {
        LinkedList *neighbors = vertices[i].outNeighbours;
        LinkedListNode *node = (*neighbors).head;

        while (node) {
            Vertex *neighbor = (Vertex *)(*node).data; // Neighbor vertex from the edge
            inDegree[(*neighbor).id]++;                // Increment in-degree of the neighbor
            node = (*node).next;                       // Move to the next edge
        }
    }

    // Create a queue and enqueue vertices with in-degree 0
    LinkedList *queue = LinkedList_new();
    if (!queue) {
        printf("Error: Failed to create a queue.\n");
        free(inDegree);
        return;
    }

    for (int i = 0; i < (*g).numVertices; i++) {
        if (inDegree[i] == 0) {
            LinkedList_append(queue, &vertices[i]);
        }
    }

    // Traverse the queue and process vertices
    int processedCount = 0;
    LinkedList *topologicalOrder = LinkedList_new();
    if (!topologicalOrder) {
        printf("Error: Creating topological list failed.\n");
        free(inDegree);
        LinkedList_delete(queue);
        return;
    }

    while ((*queue).size > 0) {
        Vertex *vertex = (Vertex *)LinkedList_popFront(queue); // Dequeue a vertex
        LinkedList_append(topologicalOrder, vertex);           // Add to topological order
        processedCount++;

        // Reduce in-degree of outgoing neighbors
        LinkedListNode *currentNode = (*vertex).outNeighbours->head;
        while (currentNode) {
            Vertex *neighbor = (Vertex *)(*currentNode).data;  // Neighbor vertex
            inDegree[(*neighbor).id]--;                        // Decrement in-degree

            // If in-degree becomes zero, enqueue the neighbor
            if (inDegree[(*neighbor).id] == 0) {
                LinkedList_append(queue, neighbor);
            }
            currentNode = (*currentNode).next; // Move to next neighbor
        }
    }

    // Check for cycles and print the result
    if (processedCount < (*g).numVertices) {
        printf("CYCLE DETECTED!\n");
    } else {
        // Print vertices in topological order
        LinkedListNode *currentNode = (*topologicalOrder).head;
        int first = 1;
        while (currentNode) {
            Vertex *vertex = (Vertex *)(*currentNode).data;
            if (!first) {
                printf(", ");
            }
            printf("%d", (*vertex).id);
            first = 0;
            currentNode = (*currentNode).next;
        }
        printf("\n");
    }

    // Cleanup
    free(inDegree);
    LinkedList_delete(queue);
    LinkedList_delete(topologicalOrder);
}

