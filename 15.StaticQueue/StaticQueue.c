#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>

typedef int bool;

#define true 1
#define false 0

#define MAX_ITEMS 50

typedef int Key;

typedef struct {
    Key Id;
} Item;

typedef struct {
    Item Items[MAX_ITEMS];
    int StartIndex;
    int Count;
} Queue;

void InitQueue(Queue* queuePointer) {
    queuePointer->StartIndex = 0;
    queuePointer->Count = 0;
}

int Count(Queue* queuePointer) {
    return queuePointer->Count;
}

void ShowQueue(Queue* queuePointer) {
    printf("Fila: \"");
    int currentIndex = queuePointer->StartIndex;
    int counter;
    for (counter = 0; counter < queuePointer->Count; counter++) {
        printf("%i ", queuePointer->Items[currentIndex]);
        currentIndex = (currentIndex + 1) % MAX_ITEMS;
    }
    printf("\"\n");
}

bool Insert(Queue* queuePointer, Item item) {
    if (queuePointer->Count >= MAX_ITEMS) {
        return false;
    }

    int position = (queuePointer->StartIndex + queuePointer->Count) % MAX_ITEMS;
    queuePointer->Items[position] = item;
    queuePointer->Count++;
    return true;
}

bool Delete(Queue* queuePointer, Item* deletedItem) {
    if (queuePointer->Count == 0) {
        return false;
    }

    *deletedItem = queuePointer->Items[queuePointer->StartIndex];
    queuePointer->StartIndex = (queuePointer->StartIndex + 1) % MAX_ITEMS;
    queuePointer->Count--;
    return true;
}

void ReinitQueue(Queue* queuePointer) {
    InitQueue(queuePointer);
}

int main(void) {
    setlocale(LC_ALL, "");
    
    Queue queue;
    InitQueue(&queue);
    ShowQueue(&queue);
    printf("A fila possui %i elementos\n", Count(&queue));

    Item item;

    item.Id = 1;
    Insert(&queue, item);
    ShowQueue(&queue);
    printf("A fila possui %i elementos\n", Count(&queue));
    
    item.Id = 2;
    Insert(&queue, item);
    ShowQueue(&queue);
    printf("A fila possui %i elementos\n", Count(&queue));

    item.Id = 3;
    Insert(&queue, item);
    ShowQueue(&queue);
    printf("A fila possui %i elementos\n", Count(&queue));

    Item deletedItem;
    Delete(&queue, &deletedItem);
    ShowQueue(&queue);
    printf("A fila possui %i elementos\n", Count(&queue));
    
    Delete(&queue, &deletedItem);
    ShowQueue(&queue);
    printf("A fila possui %i elementos\n", Count(&queue));

    ReinitQueue(&queue);
    ShowQueue(&queue);
    printf("A fila possui %i elementos\n", Count(&queue));
    
    system("PAUSE > NUL");
    return 0;
}