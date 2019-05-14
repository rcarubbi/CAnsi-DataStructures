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
    struct this* PreviousItem;
    struct this* NextItem;
} DeckItem;

typedef DeckItem* DeckItemPointer;

typedef struct {
    DeckItemPointer Header;
} Deck;

void InitDeck(Deck* deckPointer) {
    deckPointer->Header = (DeckItemPointer) malloc(sizeof(DeckItem));
    deckPointer->Header->NextItem = deckPointer->Header;
    deckPointer->Header->PreviousItem = deckPointer->Header;
}

int Count(Deck* deckPointer) {
    int counter = 0;
    DeckItemPointer currentItem = deckPointer->Header->NextItem;
    while (currentItem != deckPointer->Header) {
        counter++;
        currentItem = currentItem->NextItem;
    }
    return counter;
}

void ShowDeckFromEnd(Deck* deckPointer) {
    DeckItemPointer currentItem = deckPointer->Header->PreviousItem;
    printf("Deque partindo do fim: \"");
    while (currentItem != deckPointer->Header) {
        printf("%i ", currentItem->Item.Id);
        currentItem = currentItem->PreviousItem;
    }
    printf("\"\n");
}

void ShowDeckFromStart(Deck* deckPointer) {
    DeckItemPointer currentItem = deckPointer->Header->NextItem;
    printf("Deque partindo do início: \"");
    while (currentItem != deckPointer->Header) {
        printf("%i ", currentItem->Item.Id);
        currentItem = currentItem->NextItem;
    }
    printf("\"\n");
}

bool InsertAtEnd(Deck* deckPointer, Item item) {
    DeckItemPointer newItem = (DeckItemPointer) malloc(sizeof(DeckItem));
    newItem->Item = item;
    newItem->NextItem = deckPointer->Header;
    newItem->PreviousItem = deckPointer->Header->PreviousItem;
    deckPointer->Header->PreviousItem = newItem;
    newItem->PreviousItem->NextItem = newItem;
    return true;
}

bool InsertAtStart(Deck* deckPointer, Item item) {
    DeckItemPointer newItem = (DeckItemPointer) malloc(sizeof(DeckItem));
    newItem->Item = item;
    newItem->PreviousItem = deckPointer->Header;
    newItem->NextItem = deckPointer->Header->NextItem;
    deckPointer->Header->NextItem = newItem;   
    newItem->NextItem->PreviousItem = newItem;
    return true;
}

bool DeleteFromStart(Deck* deckPointer, Item* item) {
    if (deckPointer->Header->NextItem == deckPointer->Header) {
        return false;
    }

    DeckItemPointer itemToDelete = deckPointer->Header->NextItem;
    *item = itemToDelete->Item;
    deckPointer->Header->NextItem = itemToDelete->NextItem;
    itemToDelete->NextItem->PreviousItem = deckPointer->Header;
    free(itemToDelete);
    return true;
}


bool DeleteFromEnd(Deck* deckPointer, Item* item) {
    if (deckPointer->Header->PreviousItem == deckPointer->Header) {
        return false;
    }

    DeckItemPointer itemToDelete = deckPointer->Header->PreviousItem;
    *item = itemToDelete->Item;
    deckPointer->Header->PreviousItem = itemToDelete->PreviousItem;
    itemToDelete->PreviousItem->NextItem = deckPointer->Header;
    free(itemToDelete);
    return true;
}

void ReinitDeck(Deck* deckPointer) {
    DeckItemPointer currentItem = deckPointer->Header->NextItem;
    while (currentItem != deckPointer->Header) {
        DeckItemPointer itemToDelete = currentItem;
        currentItem = currentItem->NextItem;
        free(itemToDelete);
    }
    deckPointer->Header->NextItem = deckPointer->Header;
    deckPointer->Header->PreviousItem = deckPointer->Header;
}

int main(void) {
    setlocale(LC_ALL, "");
    
    Deck deck;
    InitDeck(&deck);
    ShowDeckFromStart(&deck);
    ShowDeckFromEnd(&deck);
    printf("O Deck possui %i elementos\n", Count(&deck));

    Item item;
    item.Id = 1;
    InsertAtStart(&deck, item);
    ShowDeckFromStart(&deck);
    ShowDeckFromEnd(&deck);
    printf("O Deck possui %i elementos\n", Count(&deck));

    item.Id = 2;
    InsertAtStart(&deck, item);
    ShowDeckFromStart(&deck);
    ShowDeckFromEnd(&deck);
    printf("O Deck possui %i elementos\n", Count(&deck));

    item.Id = 3;
    InsertAtStart(&deck, item);
    ShowDeckFromStart(&deck);
    ShowDeckFromEnd(&deck);
    printf("O Deck possui %i elementos\n", Count(&deck));

    item.Id = 6;
    InsertAtEnd(&deck, item);
    ShowDeckFromStart(&deck);
    ShowDeckFromEnd(&deck);
    printf("O Deck possui %i elementos\n", Count(&deck));

    item.Id = 5;
    InsertAtEnd(&deck, item);
    ShowDeckFromStart(&deck);
    ShowDeckFromEnd(&deck);
    printf("O Deck possui %i elementos\n", Count(&deck));

    item.Id = 4;
    InsertAtEnd(&deck, item);
    ShowDeckFromStart(&deck);
    ShowDeckFromEnd(&deck);
    printf("O Deck possui %i elementos\n", Count(&deck));

    Item deletedItem;
    if (DeleteFromEnd(&deck, &deletedItem)) {
        printf("Item %i excluído do fim com sucesso\n", deletedItem.Id);
        ShowDeckFromStart(&deck);
        ShowDeckFromEnd(&deck);
        printf("O Deck possui %i elementos\n", Count(&deck));
    }

    if (DeleteFromStart(&deck, &deletedItem)) {
        printf("Item %i excluído do início com sucesso\n", deletedItem.Id);
        ShowDeckFromStart(&deck);
        ShowDeckFromEnd(&deck);
        printf("O Deck possui %i elementos\n", Count(&deck));
    }


    ReinitDeck(&deck);
    ShowDeckFromStart(&deck);
    ShowDeckFromEnd(&deck);
    printf("O Deck possui %i elementos\n", Count(&deck));

    system("PAUSE > NUL");
    return 0;
}