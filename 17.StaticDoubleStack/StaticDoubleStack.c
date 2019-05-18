#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

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
    int Top1;
    int Top2;
} DoubleStack;

void Init(DoubleStack* stackPointer) {
    stackPointer->Top1 = -1;
    stackPointer->Top2 = MAX_ITEMS;
}

int Count(DoubleStack* stackPointer) {
    return stackPointer->Top1 + 1 + MAX_ITEMS - stackPointer->Top2;
}

bool ShowStack(DoubleStack* stackPointer, int stackNumber) {
    if (stackNumber < 1 || stackNumber > 2) {
        return false;
    } 

    printf("Pilha %i: \"", stackNumber);
    int index;
    if (stackNumber == 1) {
        for (index = stackPointer->Top1; index>=0; index--) {
            printf("%i ", stackPointer->Items[index].Id);
        }
    } else {
        for(index = stackPointer->Top2; index < MAX_ITEMS; index++){
            printf("%i ", stackPointer->Items[index].Id);            
        }
    }
    printf("\"\n");
    return true;
}

bool Push(DoubleStack* stackPointer, int stackNumber, Item item) {
    if (stackNumber < 1 || stackNumber > 2) {
        return false;
    }

    if (stackPointer->Top1 + 1 == stackPointer->Top2) {
        return false;
    }

    if (stackNumber == 1) {
        stackPointer->Top1 = stackPointer->Top1 + 1;
        stackPointer->Items[stackPointer->Top1] = item;
    } else {
        stackPointer->Top2 = stackPointer->Top2 - 1;
        stackPointer->Items[stackPointer->Top2] = item;
    }

    return true;
}

bool Pop(DoubleStack* stackPointer, int stackNumber, Item* removedItem) {
    if (stackNumber < 1 || stackNumber > 2) {
        return false;
    }

    if (stackNumber == 1) {
        if (stackPointer->Top1 == -1) {
            return false;
        }

        *removedItem = stackPointer->Items[stackPointer->Top1];
        stackPointer->Top1 = stackPointer->Top1 - 1;
    } else {
        if (stackPointer->Top2 == MAX_ITEMS) {
            return false;
        }

        *removedItem = stackPointer->Items[stackPointer->Top2];
        stackPointer->Top2 = stackPointer->Top2 + 1;
    }

    return true;
}

void Reinit(DoubleStack* stackPointer) {
    Init(stackPointer);
}

int main(void) {
    setlocale(LC_ALL, "");
    
    DoubleStack doubleStack;
    Init(&doubleStack);
    ShowStack(&doubleStack, 1);
    ShowStack(&doubleStack, 2);
    printf("A pilha possui %i elementos\n", Count(&doubleStack));

    Item item;
    
    item.Id = 1;
    Push(&doubleStack, 1, item);
    Push(&doubleStack, 2, item);
    ShowStack(&doubleStack, 1);
    ShowStack(&doubleStack, 2);
    printf("A pilha possui %i elementos\n", Count(&doubleStack));

    item.Id = 3;
    Push(&doubleStack, 1, item);
    Push(&doubleStack, 2, item);
    ShowStack(&doubleStack, 1);
    ShowStack(&doubleStack, 2);
    printf("A pilha possui %i elementos\n", Count(&doubleStack));

    item.Id = 15;
    Push(&doubleStack, 1, item);
    Push(&doubleStack, 2, item);
    ShowStack(&doubleStack, 1);
    ShowStack(&doubleStack, 2);
    printf("A pilha possui %i elementos\n", Count(&doubleStack));
    
    item.Id = 7;
    Push(&doubleStack, 1, item);
    Push(&doubleStack, 2, item);
    ShowStack(&doubleStack, 1);
    ShowStack(&doubleStack, 2);
    printf("A pilha possui %i elementos\n", Count(&doubleStack));
    
    item.Id = 2;
    Push(&doubleStack, 1, item);
    Push(&doubleStack, 2, item);
    ShowStack(&doubleStack, 1);
    ShowStack(&doubleStack, 2);
    printf("A pilha possui %i elementos\n", Count(&doubleStack));

    Item removedItem;
    
    while (Pop(&doubleStack, 1, &removedItem)) {
        printf("Item %i removido com sucesso\n", removedItem.Id);
        ShowStack(&doubleStack, 1);
        printf("A pilha possui %i elementos\n", Count(&doubleStack));
    }

      while (Pop(&doubleStack, 2, &removedItem)) {
        printf("Item %i removido com sucesso\n", removedItem.Id);
        ShowStack(&doubleStack, 2);
        printf("A pilha possui %i elementos\n", Count(&doubleStack));
    }

    Reinit(&doubleStack);
    ShowStack(&doubleStack, 1);
    ShowStack(&doubleStack, 2);
    printf("A pilha possui %i elementos\n", Count(&doubleStack));

    system("PAUSE > NUL");
    return 0;
}