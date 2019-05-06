#include <stdio.h>

#define MAX_NODES 50
#define EMPTY_NODE -1

typedef int Key;

typedef struct {
    Key Id;    
} Item;

typedef struct {
    Item Item;
    int Next;
} ListNode;

typedef struct {
    ListNode Nodes[MAX_NODES];
    int FirstNode;
    int FirstBlankNode;
} LinkedList;

void InitList(LinkedList* listPointer) {
    int index;
    for(index = 0; index < MAX_NODES-1; index++) {
        listPointer->Nodes[index].Next = index + 1;
    }
    listPointer->Nodes[MAX_NODES-1].Next = EMPTY_NODE;
    listPointer->FirstBlankNode = 0;
    listPointer->FirstNode = EMPTY_NODE;
}

int Count(LinkedList* listPointer) {
    int counter = 0;
    int index = listPointer->FirstNode;  
    while (index != EMPTY_NODE) {
        counter++;
        index = listPointer->Nodes[index].Next;
    }

    return counter;
}

void ShowList(LinkedList* listPointer) {
    int index = listPointer->FirstNode;
    printf("Lista: \" ");
    while (index != EMPTY_NODE) {
        printf("%i ", listPointer->Nodes[index].Item.Id);
        index = listPointer->Nodes[index].Next;
    }
    printf("\"\n");
}

int SequentialOrderedSearch(LinkedList* listPointer, Key id) {
    int index = listPointer->FirstNode;
    while (index != EMPTY_NODE && listPointer->Nodes[index].Item.Id < id) {
        index = listPointer->Nodes[index].Next;
    }

    if (index != EMPTY_NODE && listPointer->Nodes[index].Item.Id == id) {
        return index;
    } else {
        return EMPTY_NODE;
    }
}

int main() {
    return 0;
}