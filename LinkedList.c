#include <stdlib.h>
#include "LinkedList.h"

LinkedList *LinkedList_new() {
    LinkedList *ll = (LinkedList *)malloc(sizeof(LinkedList));
    if (!ll) return NULL; 

    (*ll).head = NULL;
    (*ll).tail = NULL;
    (*ll).size = 0;
    return ll;
}

void LinkedList_delete(LinkedList *ll) {
    //if (!ll) return;

    LinkedListNode *current = (*ll).head;
    while (current) {
        LinkedListNode *next = (*current).next;
        free(current); 
        current = next; 
    }
    free(ll); 
}

LinkedListNode *LinkedList_append(LinkedList *ll, void *elem) {
    if (!ll) return NULL;

    LinkedListNode *node = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    if (!node) return NULL; 

    (*node).data = elem;
    (*node).next = NULL;
    (*node).prev = (*ll).tail;

    if ((*ll).tail) {
        (*(*ll).tail).next = node;
    } else {
        (*ll).head = node; // First element in the list
    }

    (*ll).tail = node;
    (*ll).size++;
    return node;
}

void *LinkedList_popFront(LinkedList *ll) {
    if (!ll || (*ll).size == 0) return NULL;

    LinkedListNode *node = (*ll).head;
    void *data = (*node).data;

    (*ll).head = (*node).next;
    if ((*ll).head) {
        (*(*ll).head).prev = NULL;
    } else {
        (*ll).tail = NULL; // List is now empty
    }

    free(node);
    (*ll).size--;
    return data;
}
