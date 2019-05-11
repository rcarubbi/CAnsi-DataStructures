#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_ITEMS 50

typedef int bool;
#define true 1
#define false 0

typedef int Key;

typedef struct {
    Key Id;
} Item;

typedef struct {
    Item Items[MAX_ITEMS];
    int Top;
} Stack;

void InitStack(Stack* stackPointer) {
    stackPointer->Top = -1;
}

int Count(Stack* stackPointer) {
    return stackPointer->Top + 1;
}

void ShowStack(Stack* stackPointer) {
    int itemIndex;
    printf("Pilha: \" ");
    for (itemIndex = stackPointer->Top; itemIndex >= 0; itemIndex--) {
        printf("%i ", stackPointer->Items[itemIndex].Id);
    }
    printf("\"\n");
}

bool Push(Stack* stackPointer, Item item) {
    if (stackPointer->Top >= MAX_ITEMS) {
        return false;
    }

    stackPointer->Top++;
    stackPointer->Items[stackPointer->Top] = item;
    return true; 
}

bool Pop(Stack* stackPointer, Item* removedItem) {
    if (stackPointer->Top == -1) {
        return false;
    }
    *removedItem = stackPointer->Items[stackPointer->Top];
    stackPointer->Top--;
    return true;
}

void Reinit(Stack* stackPointer) {
    stackPointer->Top = -1;
}

int main(void) {
    setlocale(LC_ALL, "");
    Stack stack;
    InitStack(&stack);
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