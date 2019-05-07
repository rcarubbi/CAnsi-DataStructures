#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define true 1
#define false 0

#define NOTFOUND -1
#define MAX_ITEMS 50

typedef int bool;
typedef int Key;

typedef struct {
    Key Id;
} Item;

typedef struct {
    Item Items[MAX_ITEMS];
    int Count;
} List;

void InitializeList(List* listPointer) {
    listPointer->Count = 0;
}

int GetSize(List* listPointer) {
    return listPointer->Count;
}

void ShowList(List* listPointer) {
    int counter;
    printf("Lista: \" ");
    for(counter=0; counter < listPointer->Count; counter++) {
        printf("%i ", listPointer->Items[counter].Id);
    }
    printf("\"\n");
}

int SequentialSearch(List* listPointer, Key id) {
    int counter = 0;
    while(counter < listPointer->Count) {
        if (id==listPointer->Items[counter].Id) {
            return counter;
        } else {
            counter++;
        }
    }
    return NOTFOUND;
}

bool InsertItemAt(List* listPointer, Item item, int position) {
    int index;
    if (listPointer->Count == MAX_ITEMS
        || position < 0 
        || position > listPointer->Count)
    {
        return false;
    }

    for(index = listPointer->Count; index > position; index--) {
        listPointer->Items[index] = listPointer->Items[index-1];
    }

    listPointer->Items[position] = item;
    listPointer->Count++;
    return true;
}

bool DeleteItem(List* listPointer, Key id)
{
    int position, index;
    position = SequentialSearch(listPointer, id);

    if (position == NOTFOUND) {
         return false;
    }

    for(index = position; index < listPointer->Count; index++) {
        listPointer->Items[index] = listPointer->Items[index+1];
    }
    listPointer->Count--;
    return true;
}

void ReinitList(List* listPointer) {
    listPointer->Count = 0;
}

int main() {
    setlocale(LC_ALL, "");
    List list;
    
    InitializeList(&list);
    ShowList(&list);
    
    printf("Número de elementos na lista: %i.\n", GetSize(&list));
    
    Item item;
    
    item.Id = 9;
    InsertItemAt(&list, item, 0);
    
    ShowList(&list);
    
    item.Id = 3;
    InsertItemAt(&list, item, 1);
    
    item.Id = 4;
    InsertItemAt(&list, item, 2);
    
    item.Id = 1;
    InsertItemAt(&list, item, 3);

    item.Id = 12;
    InsertItemAt(&list, item, 2);
    
    ShowList(&list);
    printf("Número de elementos na lista: %i.\n", GetSize(&list));
 
    printf("Chave 4 encontrada na posição: %i do arranjo Items.\n", SequentialSearch(&list, 4));
  
    if (DeleteItem(&list, 4)) printf("Exclusão bem sucedida: 4.\n");
    if (DeleteItem(&list, 8)) printf("Exclusão bem sucedida: 8.\n");
    if (DeleteItem(&list, 9)) printf("Exclusão bem sucedida: 9.\n");
    ShowList(&list);
    printf("Número de elementos na lista: %i.\n", GetSize(&list));
 
    ReinitList(&list);
    ShowList(&list);
    printf("Número de elementos na lista: %i.\n",GetSize(&list));
    
    system("Pause >> NULL");
    return 0;
}