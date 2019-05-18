#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>

typedef int bool;

#define true 1
#define false 0

typedef struct this {
    float Value;
    int Column;
    struct this* NextNode;
} Node, * NodePointer;

typedef struct {
    NodePointer* Nodes;
    int Lines;
    int Columns;
} Matrix;

void Init(Matrix* matrixPointer, int lines, int columns) {
    int index;
    matrixPointer->Lines = lines;
    matrixPointer->Columns = columns;
    matrixPointer->Nodes = (NodePointer*) malloc(lines * sizeof(NodePointer));
    for (index = 0; index < lines; index++) {
        matrixPointer->Nodes[index] = NULL;
    }
}

bool Set(Matrix* matrixPointer, int line, int column, float value) {
    if (line < 0 || line >= matrixPointer->Lines ||
        column < 0 || column >= matrixPointer->Columns) {
            return false;
    }

    NodePointer previousNode = NULL;
    NodePointer currentNode = matrixPointer->Nodes[line];

    while (currentNode != NULL && currentNode->Column < column) {
        previousNode = currentNode;
        currentNode = currentNode->NextNode;
    }

    if (currentNode != NULL && currentNode->Column == column) {
        if (value == 0) {
            if (previousNode == NULL) {
                matrixPointer->Nodes[line] = currentNode->NextNode;
            } else {
                previousNode->NextNode = currentNode->NextNode;
            }
            free(currentNode);
        } else {
            currentNode->Value = value;
        }
    } else {
        NodePointer newNode = (NodePointer) malloc(sizeof(Node));
        newNode->Column = column;
        newNode->Value = value;
        newNode->NextNode = currentNode;

        if(previousNode == NULL) {
            matrixPointer->Nodes[line] = newNode;
        } else {
            previousNode->NextNode = newNode;
        }
    }
    return true;
}

float Get(Matrix* matrixPointer, int line, int column) {
    if (line < 0 || line >= matrixPointer->Lines ||
        column < 0 || column >= matrixPointer->Columns) {
            return 0;
    }

    NodePointer currentNode = matrixPointer->Nodes[line];

    while(currentNode != NULL && currentNode->Column < column) {
        currentNode = currentNode->NextNode;
    }

    if (currentNode != NULL && currentNode->Column == column) {
        return currentNode->Value;
    } else {
        return 0;
    }
}



int main(void) {
    setlocale(LC_ALL, "");
    
    Matrix newMatrix;

    Init(&newMatrix, 10, 10);

    printf("Set(&newMatrix, 4, 3, 12.3); = %i\n", Set(&newMatrix, 4, 3, 12.3));
    printf("Set(&newMatrix, 4, 3, 14.2); = %i\n", Set(&newMatrix, 4, 3, 14.2));
    printf("Set(&newMatrix,  1, 4, 3.2); = %i\n", Set(&newMatrix, 1, 4, 3.2));
    printf("Set(&newMatrix, 7, 3, 10.4); = %i\n", Set(&newMatrix, 7, 3, 10.4));
    printf("Set(&newMatrix, 12, 12, 12.3); = %i\n", Set(&newMatrix, 12, 12, 12.3));
    printf("Set(&newMatrix,  7, 4, 12.3); = %i\n", Set(&newMatrix, 7, 4, 12.3));
    printf("Set(&newMatrix, 7, 3, 0); = %i\n",  Set(&newMatrix, 7, 3, 0));

    printf("Get(&newMatrix, 4, 3); = %f\n", Get(&newMatrix, 4, 3));
    printf("Get(&newMatrix, 1, 4); = %f\n", Get(&newMatrix, 1, 4));
    printf("Get(&newMatrix, 7, 3); = %f\n", Get(&newMatrix, 7, 3));
    printf("Get(&newMatrix, 12, 12); = %f\n", Get(&newMatrix, 12, 12));
    printf("Get(&newMatrix, 7, 4); = %f\n", Get(&newMatrix, 7, 4));
    printf("Get(&newMatrix, 4, 4); = %f\n", Get(&newMatrix, 4, 4));

    system("PAUSE > NUL");
    return 0;
}