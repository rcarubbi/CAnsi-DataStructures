#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>

typedef int bool;

#define true 1
#define false 0

typedef int Key;
typedef struct this {
    Key Id;
    struct this *Left;
    struct this *Right;
    int Height;
} Node, *NodePointer;

NodePointer CreateNode(Key id) {
    NodePointer newNode = (NodePointer)malloc(sizeof(Node));
    newNode->Id = id;
    newNode->Left = NULL;
    newNode->Right = NULL;
    newNode->Height = 0;
}

NodePointer Init() {
    return (NULL);
}

int Max(int a, int b) {
    if (a > b) return a;
    return b;
}

int GetHeight(NodePointer root) {
    if (!root) return -1;
    return root->Height;
}

NodePointer RotateRight(NodePointer root) {
    NodePointer newRoot;
    newRoot = root->Left;
    root->Left = newRoot->Right;
    newRoot->Right = root;

    root->Height = Max(GetHeight(root->Right), GetHeight(root->Left)) + 1;
    newRoot->Height = Max(GetHeight(newRoot->Left), root->Height) + 1;

    return newRoot;
}

NodePointer RotateLeft(NodePointer root) {
    NodePointer newRoot;
    newRoot = root->Right;
    root->Right = newRoot->Left;
    newRoot->Left = root;

    root->Height = Max(GetHeight(root->Right), GetHeight(root->Left)) + 1;
    newRoot->Height = Max(GetHeight(newRoot->Right), root->Height) + 1;
    
    return newRoot;
}

NodePointer RotateLeftRight(NodePointer root) {
    root->Left = RotateLeft(root->Left);
    return RotateRight(root);
}

NodePointer RotateRightLeft(NodePointer root) {
    root->Right = RotateRight(root->Right);
    return RotateLeft(root);
}

NodePointer Insert(NodePointer root, Key id) {
    if (!root) return CreateNode(id);
    if (id < root->Id) {
        root->Left = Insert(root->Left, id);
        if (GetHeight(root->Left) - GetHeight(root->Right) == 2) {
            if (id < root->Left->Id) {
                root = RotateRight(root);
            } else {
                root = RotateLeftRight(root);
            }
        }  
    } else if (id > root->Id) {
        root->Right = Insert(root->Right, id);
        if (GetHeight(root->Right) - GetHeight(root->Left) == 2) {
            if (id > root->Right->Id) {
                root = RotateLeft(root);
            } else {
                root = RotateRightLeft(root);
            }
        }
    }
    root->Height = Max(GetHeight(root->Left), GetHeight(root->Right)) + 1;
    return root;
}

void ShowTree(NodePointer root) {
    if (root != NULL) {
        printf("%i", root->Id);
        printf("(");
        ShowTree(root->Left);
        ShowTree(root->Right);
        printf(")");
    }
}

int main(void) {
    setlocale(LC_ALL, "");
    
    NodePointer root = Init();
    root = Insert(root, 2);
    root = Insert(root, 3);
    root = Insert(root, 4);
    root = Insert(root, 5);
    root = Insert(root, 8);
    root = Insert(root, 12);
    root = Insert(root, 20);
    root = Insert(root, 25);
    root = Insert(root, 7);
    root = Insert(root, 1);
    root = Insert(root, 45);

    ShowTree(root);

    system("PAUSE > NUL");
    return 0;
}