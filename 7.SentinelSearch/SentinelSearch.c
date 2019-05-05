#include <stdio.h>

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
    Item Items[MAX_ITEMS+1];
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

int SentinelSearch(List* listPointer, Key id) {
    int index = 0;
    listPointer->Items[listPointer->Count].Id = id;
    while(listPointer->Items[index].Id != id) {
        index++;
    }

    if (index == listPointer->Count) {
        return NOTFOUND;
    } else {
        return index;
    }
}

bool insertItemAt(List* listPointer, Item item, int position) {
    int index;
    if (listPointer->Count == MAX_ITEMS || position < 0 || position > listPointer->Count) {
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
    position = SentinelSearch(listPointer, id);
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
    List list; InitializeList(&list);
    Item item;

    ShowList(&list);
    printf("Numero de elementos na lista: %i.\n", GetSize(&list));
    
    item.Id = 9;
    insertItemAt(&list, item, 0);

    ShowList(&list);
    
    item.Id = 3;
    insertItemAt(&list, item, 1);
    item.Id = 4;
    insertItemAt(&list, item, 2);
    item.Id = 1;
    insertItemAt(&list, item, 3);
    item.Id = 12;
    insertItemAt(&list, item, 2);

    ShowList(&list);
    printf("Numero de elementos na lista: %i.\n", GetSize(&list));
 
    printf("Chave 4 encontrada na posicao: %i do arranjo Items.\n", SentinelSearch(&list, 4));
  
    if (DeleteItem(&list,4)) printf("Exclusao bem sucedida: 4.\n");
    if (DeleteItem(&list,8)) printf("Exclusao bem sucedida: 8.\n");
    if (DeleteItem(&list,9)) printf("Exclusao bem sucedida: 9.\n");
    
    ShowList(&list);
    printf("Numero de elementos na lista: %i.\n", GetSize(&list));
 
    ReinitList(&list);

    ShowList(&list);
    printf("Numero de elementos na lista: %i.\n", GetSize(&list));
 
    getchar();
    return 0;
}