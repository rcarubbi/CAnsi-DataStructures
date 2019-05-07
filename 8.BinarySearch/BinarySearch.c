#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define true 1
#define false 0
#define MAX_ITEMS 50
#define NOTFOUND -1

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
    int index;
    printf("Lista: \" ");
    for(index = 0; index < listPointer->Count; index++) {
        printf("%i ", listPointer->Items[index].Id);
    }
    printf("\"\n");
}

int BinarySearch(List* listPointer, Key id) {
    int left, right, middle;
    left = 0;
    right = listPointer->Count-1;
    while (left <= right) {
        middle = (left +  right) / 2;
        if (listPointer->Items[middle].Id == id) {
            return middle;
        }
        else if (listPointer->Items[middle].Id < id) {
            left = middle + 1;
        }
        else {
            right = middle - 1;
        }
    }
    return NOTFOUND;
}

bool InsertOrderedItem(List* listPointer, Item item) {
    
    if (listPointer->Count >= MAX_ITEMS) {
        return false;
    }

    int position = listPointer->Count;
     
    while(position > 0 && listPointer->Items[position-1].Id > item.Id) {
        listPointer->Items[position] = listPointer->Items[position-1];
        position--;
    }

    listPointer->Items[position] = item;
    listPointer->Count++;
    return true;
}

bool DeleteItem(List* listPointer, Key id)
{
    int position, index;
    position = BinarySearch(listPointer, id);
    if (position == NOTFOUND) return false;

    for(index = position; index < listPointer->Count; index++) {
        listPointer->Items[index] = listPointer->Items[index + 1];
    }
    
    listPointer->Count--;
    return true;
}

void ReinitList(List* listPointer) {
    listPointer->Count = 0;
}

int main() {
    setlocale(LC_ALL, "");
    
    List list; InitializeList(&list);
    Item item;

    ShowList(&list);
    printf("Número de elementos na lista: %i.\n", GetSize(&list));
    
    item.Id = 9;
    InsertOrderedItem(&list, item);

    ShowList(&list);
    
    item.Id = 3;
    InsertOrderedItem(&list, item);
    item.Id = 4;
    InsertOrderedItem(&list, item);
    item.Id = 1;
    InsertOrderedItem(&list, item);
    item.Id = 12;
    InsertOrderedItem(&list, item);

    ShowList(&list);
    printf("Número de elementos na lista: %i.\n", GetSize(&list));
 
    printf("Chave 4 encontrada na posição: %i do arranjo Items.\n", BinarySearch(&list, 4));
  
    if (DeleteItem(&list,4)) printf("Exclusão bem sucedida: 4.\n");
    if (DeleteItem(&list,8)) printf("Exclusão bem sucedida: 8.\n");
    if (DeleteItem(&list,9)) printf("Exclusão bem sucedida: 9.\n");
    
    ShowList(&list);
    printf("Número de elementos na lista: %i.\n", GetSize(&list));
 
    ReinitList(&list);

    ShowList(&list);
    printf("Número de elementos na lista: %i.\n", GetSize(&list));
 
    system("PAUSE >> NULL");
    return 0;
}
