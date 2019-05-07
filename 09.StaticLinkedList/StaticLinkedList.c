#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_NODES 50
#define EMPTY_NODE -1
#define true 1
#define false 0

typedef int bool;

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
    listPointer->FirstBlankNode = 0;
    listPointer->FirstNode = EMPTY_NODE;
    
    for(index = 0; index < MAX_NODES-1; index++) {
        listPointer->Nodes[index].Next = index + 1;
    }
    
    listPointer->Nodes[MAX_NODES-1].Next = EMPTY_NODE;
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

int GetBlankNode(LinkedList* listPointer) {
    int firstBlankNode = listPointer->FirstBlankNode;
    if (listPointer->FirstBlankNode != EMPTY_NODE) {
        listPointer->FirstBlankNode = listPointer->Nodes[listPointer->FirstBlankNode].Next;
    }
    return firstBlankNode; 
}

bool InsertNode(LinkedList* listPointer, Item item) {
    if (listPointer->FirstBlankNode == EMPTY_NODE) {
        return false;
    } 

    int previousNode = EMPTY_NODE;
    int currentNode = listPointer->FirstNode;
    Key id = item.Id;

    while(currentNode != EMPTY_NODE 
          && listPointer->Nodes[currentNode].Item.Id < id) 
    {
        previousNode = currentNode;
        currentNode = listPointer->Nodes[currentNode].Next;  
    }

    if (currentNode != EMPTY_NODE && listPointer->Nodes[currentNode].Item.Id == id) {
        return false;
    }

    currentNode = GetBlankNode(listPointer);
    listPointer->Nodes[currentNode].Item = item;

    if (previousNode == EMPTY_NODE) {
        listPointer->Nodes[currentNode].Next = listPointer->FirstNode;
        listPointer->FirstNode = currentNode;
    } else {
        listPointer->Nodes[currentNode].Next = listPointer->Nodes[previousNode].Next;
        listPointer->Nodes[previousNode].Next = currentNode;
    }
    return true;
}

void SetBlankNode(LinkedList* listPointer, int node) {
    listPointer->Nodes[node].Next = listPointer->FirstBlankNode;
    listPointer->FirstBlankNode = node;
}

bool DeleteItem(LinkedList* listPointer, Key id) {
    int previousNode = EMPTY_NODE;
    int currentNode = listPointer->FirstNode;

    while(currentNode != EMPTY_NODE 
          && listPointer->Nodes[currentNode].Item.Id < id) 
    {   
        previousNode = currentNode;
        currentNode = listPointer->Nodes[currentNode].Next;  
    }

    if (currentNode == EMPTY_NODE || listPointer->Nodes[currentNode].Item.Id != id) {
        return false;
    }
    else {
        if (previousNode == EMPTY_NODE) {
            listPointer->FirstNode = listPointer->Nodes[currentNode].Next;
        } else {
            listPointer->Nodes[previousNode].Next = listPointer->Nodes[currentNode].Next;   
        }
        SetBlankNode(listPointer, currentNode);
        return true;
    }
}

void ReinitList(LinkedList* listPointer) {
    InitList(listPointer);
}

int main() {
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
    
    int index = SequentialOrderedSearch(&list, 12);
    printf("12 esta no indice %i\n", index);

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