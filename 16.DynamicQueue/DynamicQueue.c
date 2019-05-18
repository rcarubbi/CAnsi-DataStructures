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
} QueueItem, *QueueItemPointer;

typedef struct {
    QueueItemPointer Start;
    QueueItemPointer End;
} Queue;

void InitQueue(Queue* queuePointer) {
    queuePointer->Start = NULL;
    queuePointer->End = NULL;
}

int Count(Queue* queuePointer) {
    QueueItemPointer currentItem = queuePointer->Start;
    int counter = 0;
    while (currentItem != NULL) {
        counter++;
        currentItem = currentItem->Next;
    }
    return counter;
}


void ShowQueue(Queue* queuePointer) {
    QueueItemPointer currentItem = queuePointer->Start;
    printf("Fila: \"");
    while (currentItem != NULL) {
        printf("%i ", currentItem->Item.Id);
        currentItem = currentItem->Next;
    }

    printf("\"\n");
}

bool Insert(Queue* queuePointer, Item item) {
    QueueItemPointer newItem = (QueueItemPointer) malloc(sizeof(QueueItem));
    newItem->Item = item;
    newItem->Next = NULL;
    if (queuePointer->Start == NULL) {
        queuePointer->Start = newItem;
    } else {
        queuePointer->End->Next = newItem;
    }
    queuePointer->End = newItem;
    return true;
}

bool Delete(Queue* queuePointer, Item* deletedItem) {
    if (queuePointer->Start == NULL) {
        return false;
    }

    *deletedItem = queuePointer->Start->Item;
    QueueItemPointer itemToDelete = queuePointer->Start;
    queuePointer->Start = queuePointer->Start->Next;
    free(itemToDelete);
    if (queuePointer->Start == NULL) {
        queuePointer->End = NULL;
    }
}

void ReinitQueue(Queue* queuePointer) {
    QueueItemPointer currentItem = queuePointer->Start;

    while (currentItem != NULL) {
        QueueItemPointer itemToDelete = currentItem;
        currentItem = currentItem->Next;
        free(itemToDelete);
    }

    queuePointer->Start = NULL;
    queuePointer->End = NULL;
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