#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>

typedef int bool;

#define true 1
#define false 0

typedef int Key;

typedef struct {
    Key Id;    
} Item;

typedef struct this {
    Item Item;
    struct this* Next;
} ListNode;

typedef ListNode* NodePointer;

typedef struct {
    NodePointer Header;
} LinkedList;

void InitializeList(LinkedList* listPointer) {
    listPointer->Header = (NodePointer) malloc(sizeof(ListNode));
    listPointer->Header->Next = listPointer->Header;
}

int Count(LinkedList* listPointer) {
    NodePointer currentNode = listPointer->Header->Next;
    int counter = 0;
    while(currentNode != listPointer->Header) {
        counter++;
        currentNode = currentNode->Next;
    }

    return counter;
}

void ShowList(LinkedList* listPointer) {
    NodePointer currentNode = listPointer->Header->Next;
    printf("Lista: \" ");
    while (currentNode != listPointer->Header) {
        printf("%i ", currentNode->Item.Id);
        currentNode = currentNode->Next;
    }
    printf("\"\n");
}

NodePointer SentinelSearch(LinkedList* listPointer, Key id) {
    NodePointer currentNode = listPointer->Header->Next;
    listPointer->Header->Item.Id = id;
    
    while(currentNode->Item.Id != id) {
        currentNode = currentNode->Next;
    }

    if (currentNode != listPointer->Header) {
        return currentNode;
    } else {
        return NULL;
    }
}

int main(void) {
    setlocale(LC_ALL, "");
    
    system("PAUSE > NUL");
    return 0;
}