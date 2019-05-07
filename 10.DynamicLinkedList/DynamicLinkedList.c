#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
 

#define true 1
#define false 0

typedef int bool;
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
    NodePointer FirstNode;
} LinkedList;

void InitList(LinkedList* listPointer) {
    listPointer->FirstNode = NULL;
}

int Count(LinkedList* listPointer) {
    int counter = 0;
    NodePointer node  = listPointer->FirstNode;  
    while (node != NULL) {
        counter++;
        node = node->Next;
    }

    return counter;
}

void ShowList(LinkedList* listPointer) {
    NodePointer node = listPointer->FirstNode;
    printf("Lista: \" ");
    while (node != NULL) {
        printf("%i ", node->Item.Id);
        node = node->Next;
    }
    printf("\"\n");
}

NodePointer SequentialOrderedSearch(LinkedList* listPointer, Key id) {
    NodePointer node = listPointer->FirstNode;

    while (node != NULL && node->Item.Id < id) {
        node = node->Next;
    }

    if (node != NULL && node->Item.Id == id) {
        return node;
    } else {
        return NULL;
    }
}

NodePointer SequentialOrderedSearchWithPreviousNode(LinkedList* listPointer, Key id, NodePointer* previousNode) {
    *previousNode = NULL;
    NodePointer currentNode = listPointer->FirstNode;
    
    while (currentNode != NULL && currentNode->Item.Id < id){
        *previousNode = currentNode;
        currentNode = currentNode->Next;
    }

    if (currentNode != NULL && currentNode->Item.Id == id) {
        return currentNode;
    } else {
        return NULL;
    }
}

bool InsertNode(LinkedList* listPointer, Item item) {
    Key id = item.Id;
    NodePointer previousNode, nodeToInsert;
    nodeToInsert = SequentialOrderedSearchWithPreviousNode(listPointer, id, &previousNode);
    
    if (nodeToInsert != NULL) {
         return false;
    }

    nodeToInsert = (NodePointer) malloc(sizeof(ListNode));
    nodeToInsert->Item = item;

    if (previousNode == NULL) {
        nodeToInsert->Next = listPointer->FirstNode;
        listPointer->FirstNode = nodeToInsert;
    } else {
        nodeToInsert->Next = previousNode->Next;
        previousNode->Next = nodeToInsert;
    }

    return true;
}

bool DeleteItem(LinkedList* listPointer, Key id) {
    NodePointer previousNode, nodeToDelete;
    nodeToDelete = SequentialOrderedSearchWithPreviousNode(listPointer, id, &previousNode);
    if (nodeToDelete == NULL) {
        return false;
    }  

    if (previousNode == NULL) {
        listPointer->FirstNode = nodeToDelete->Next;
    } else {
        previousNode->Next = nodeToDelete->Next;
    }
    free(nodeToDelete);
    return true;
}

void ReinitList(LinkedList* listPointer) {
   NodePointer currentNode = listPointer->FirstNode;
   while (currentNode != NULL) {
       NodePointer nodeToDelete = currentNode;
       currentNode = currentNode->Next;
       free(nodeToDelete);
   }

   listPointer->FirstNode = NULL;
}

int main(void) {
    setlocale(LC_ALL, "Portuguese_Brazil");
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