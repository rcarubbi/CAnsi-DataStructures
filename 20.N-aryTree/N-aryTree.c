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
    struct this *FirstChild, *NextSibling;
} Node, * NodePointer;

NodePointer CreateNewNode(Key id) {
    NodePointer newNode = (NodePointer) malloc(sizeof(Node));
    newNode->FirstChild = NULL;
    newNode->NextSibling = NULL;
    newNode->Id = id;

    return newNode;
}

NodePointer InitTree(Key id) {
    return CreateNewNode(id);
}

NodePointer Search(Key id, NodePointer root){
    if (root == NULL) {
        return NULL;
    }
    if (root->Id == id) {
        return root;
    }

    NodePointer currentChild = root->FirstChild;
    while(currentChild) {
        NodePointer foundNode = Search(id, currentChild);
        if (foundNode) {
            return foundNode;
        }
        currentChild = currentChild->NextSibling;
    }
    return NULL;
}

bool InsertNode(NodePointer root, Key id, Key parentId) {
    NodePointer parentNode = Search(parentId, root);

    if (!parentNode) {
        return false;
    }

    NodePointer childNode = CreateNewNode(id);
    NodePointer currentChild = parentNode->FirstChild;
    if (!currentChild){
        parentNode->FirstChild = childNode;
    } else {
        while (currentChild->NextSibling) {
            currentChild = currentChild->NextSibling;
        }
        currentChild->NextSibling = childNode;
    }
    return true;
}

void ShowTree(NodePointer root) {
    if (root == NULL) {
        return;
    }

    printf("%d(", root->Id);
    NodePointer currentChild = root->FirstChild;

    while(currentChild) {
        ShowTree(currentChild);
        currentChild = currentChild->NextSibling;
    }

    printf(")");
}

int main(void) {
    setlocale(LC_ALL, "");
    
    NodePointer root = InitTree(8);

    system("PAUSE > NUL");
    return 0;
}