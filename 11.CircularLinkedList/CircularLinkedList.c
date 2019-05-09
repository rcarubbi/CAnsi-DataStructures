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

NodePointer SentinelOrderedSearch(LinkedList* listPointer, Key id) {
    NodePointer currentNode = listPointer->Header->Next;
    listPointer->Header->Item.Id = id;
    
    while(currentNode->Item.Id < id ) {
        currentNode = currentNode->Next;
    }

    if (currentNode != listPointer->Header && currentNode->Item.Id == id) {
        return currentNode;
    } else {
        return NULL;
    }
}

NodePointer SequentialSearchWithPreviousByRef(LinkedList* listPointer, Key id, NodePointer* previousNode) {
    *previousNode = listPointer->Header;
    NodePointer currentNode = listPointer->Header->Next;

    listPointer->Header->Item.Id = id;
    while(currentNode->Item.Id < id) {
        *previousNode = currentNode;
        currentNode = currentNode->Next;
    }

    if (currentNode != listPointer->Header && currentNode->Item.Id == id) {
        return currentNode;
    } else {
        return NULL;
    }
}

bool InsertOrderedItem(LinkedList* listPointer, Item item) {
    NodePointer previousNode, nodeToInsert;
    nodeToInsert = SequentialSearchWithPreviousByRef(listPointer, item.Id, &previousNode);
    
    if (nodeToInsert != NULL) {
        return false;
    } 

    nodeToInsert = (NodePointer) malloc(sizeof(Item));
    nodeToInsert->Item = item;
    nodeToInsert->Next = previousNode->Next;
    previousNode->Next = nodeToInsert;
}

bool DeleteItem(LinkedList* listPointer, Key id) {
    NodePointer previousNode, nodeToDelete;
    nodeToDelete = SequentialSearchWithPreviousByRef(listPointer, id, &previousNode);
    if (nodeToDelete == NULL){
        return false;
    } 

    previousNode->Next = nodeToDelete->Next;
    free(nodeToDelete);
    return true;
}

void ReinitList(LinkedList* listPointer) {
    NodePointer currentNode = listPointer->Header->Next;
    while(currentNode != listPointer->Header) {
        NodePointer nodeToDelete = currentNode;
        currentNode = currentNode->Next;
        free(nodeToDelete);
    }

    listPointer->Header->Next = listPointer->Header;
}

int main(void) {
    setlocale(LC_ALL, "");
    
    LinkedList list;
    Item item;
    
    InitList(&list);
    ShowList(&list);
    printf("A lista possui %i elementos\n", Count(&list));
    
    item.Id = 1;
    InsertNode(&list, item);
    ShowList(&list);
    printf("A lista possui %i elementos\n", Count(&list));
    
    item.Id = 5;
    InsertNode(&list, item);
    ShowList(&list);
     printf("A lista possui %i elementos\n", Count(&list));
    
    item.Id = 12;
    InsertNode(&list, item);
    ShowList(&list);
    printf("A lista possui %i elementos\n", Count(&list));
    
    item.Id = 9;
    InsertNode(&list, item);
    ShowList(&list);
    printf("A lista possui %i elementos\n", Count(&list));
    
    item.Id = 22;
    InsertNode(&list, item);
    ShowList(&list);
    printf("A lista possui %i elementos\n", Count(&list));
    
    item.Id = 14;
    InsertNode(&list, item);
    ShowList(&list);
    printf("A lista possui %i elementos\n", Count(&list));
    
    NodePointer node = SequentialOrderedSearch(&list, 12);
    printf("12 esta no endereço %p\n", node);

    if (DeleteItem(&list, 5)) printf("Item 5 excluído com sucesso\n");
    printf("A lista possui %i elementos\n", Count(&list));
   
    if (DeleteItem(&list, 12)) printf("Item 12 excluído com sucesso\n");
    printf("A lista possui %i elementos\n", Count(&list));

    if (DeleteItem(&list, 6)) printf("Item 6 excluído com sucesso\n");
    printf("A lista possui %i elementos\n", Count(&list));

    ShowList(&list);
    printf("A lista possui %i elementos\n", Count(&list));


    system("PAUSE > NUL");
    return 0;
}