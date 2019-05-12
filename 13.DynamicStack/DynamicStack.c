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
} StackItem;

typedef StackItem* StackItemPointer;

typedef struct {
    StackItemPointer Top;
 } Stack;

void InitializeStack(Stack* stackPointer) {
    stackPointer->Top = NULL;
}

int Count(Stack* stackPointer) {
    int counter = 0;
    StackItemPointer currentItem = stackPointer->Top;
    while (currentItem != NULL) {
        counter++;
        currentItem = currentItem->Next;
    }
    return counter;
}

bool IsEmpty(Stack* stackPointer) {
    return stackPointer->Top == NULL;
}

 void ShowStack(Stack* stackPointer) {
    StackItemPointer currentItem = stackPointer->Top;
    printf("Pilha: \"");
    while(currentItem != NULL) {
        printf("%i ", currentItem->Item.Id);
        currentItem = currentItem->Next;
    }
    printf("\"\n");
}

bool Push(Stack* stackPointer, Item item) {
    StackItemPointer newItem = (StackItemPointer) malloc(sizeof(StackItem));
    newItem->Item = item;
    newItem->Next = stackPointer->Top;
    stackPointer->Top = newItem;
    return true;
}

bool Pop(Stack* stackPointer, Item* itemByRef) {
    if (stackPointer->Top == NULL) {
        return false;
    }

    *itemByRef = stackPointer->Top->Item;
    StackItemPointer itemToDelete = stackPointer->Top;
    stackPointer->Top = stackPointer->Top->Next;
    free(itemToDelete);
    return true;
}

void Reinit(Stack* stackPointer) {
    StackItemPointer itemToDelete;
    StackItemPointer currentItem = stackPointer->Top;
    while(currentItem != NULL) {
        itemToDelete = currentItem;
        currentItem = currentItem->Next;
        free(itemToDelete);
    }
    stackPointer->Top = NULL;
}

int main(void) {
    setlocale(LC_ALL, "");
    
 Stack stack;
    InitializeStack(&stack);
    ShowStack(&stack);
    printf("A pilha possui %i elementos\n", Count(&stack));

    Item item;
    
    item.Id = 1;
    Push(&stack, item);
    ShowStack(&stack);
    printf("A pilha possui %i elementos\n", Count(&stack));

    item.Id = 3;
    Push(&stack, item);
    ShowStack(&stack);
    printf("A pilha possui %i elementos\n", Count(&stack));

    item.Id = 15;
    Push(&stack, item);
    ShowStack(&stack);
    printf("A pilha possui %i elementos\n", Count(&stack));
    
    item.Id = 7;
    Push(&stack, item);
    ShowStack(&stack);
    printf("A pilha possui %i elementos\n", Count(&stack));
    
    item.Id = 2;
    Push(&stack, item);
    ShowStack(&stack);
    printf("A pilha possui %i elementos\n", Count(&stack));

    Item removedItem;
    
    while (Pop(&stack, &removedItem)) {
        printf("Item %i removido com sucesso\n", removedItem.Id);
        ShowStack(&stack);
        printf("A pilha possui %i elementos\n", Count(&stack));
    }

    Reinit(&stack);
    ShowStack(&stack);
    printf("A pilha possui %i elementos\n", Count(&stack));

    system("PAUSE > NUL");
    return 0;
}