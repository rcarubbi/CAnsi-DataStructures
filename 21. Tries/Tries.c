#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>
#include <string.h>

typedef int bool;

#define true 1
#define false 0

#define ALPHABET_COUNT 26

typedef struct this {
    struct this *Children[ALPHABET_COUNT];
    bool ValidWord;
} Node, * NodePointer;

NodePointer CreateNode() {
    NodePointer pointer = NULL;
    pointer = (NodePointer)malloc(sizeof(Node));
    pointer->ValidWord = false;
    int index;
    for(index = 0;index<ALPHABET_COUNT;index++) {
        pointer->Children[index] = NULL;
    }
    return pointer;
}

NodePointer Init() {
    return CreateNode();
}

int MapIndex(char letter) {
    return (int)letter - (int)'a';
}

void Add(NodePointer root, char *word) {
    int height;
    int wordLength = strlen(word);
    int index;

    NodePointer pointer = root;
    for (height = 0; height < wordLength; height++) {
        index = MapIndex(word[height]);
        if (!pointer->Children[index]) {
            pointer->Children[index] = CreateNode();
        }
        pointer = pointer->Children[index];
    }
    pointer->ValidWord = true;
}

bool Search(NodePointer root, char *word) {
    int height;
    int wordLength = strlen(word);
    int index;

    NodePointer pointer = root;
    for (height = 0; height < wordLength; height++) {
        index = MapIndex(word[height]);
        if (!pointer->Children[index]) {
            return false;
        }
        pointer = pointer->Children[index];
    }

    return pointer->ValidWord;
}

int main(void) {
    setlocale(LC_ALL, "");
    NodePointer root = Init();

    Add(root, "come");
    Add(root, "começo");
    Add(root, "ar");
    Add(root, "ter");
    Add(root, "cal");
    Add(root, "campo");
    Add(root, "com");

    bool result = Search(root, "carro");
    printf("Carro: %d\n", result);

    bool result2 = Search(root, "come");
    printf("Come: %d\n", result2);

    system("PAUSE > NUL");
    return 0;
}