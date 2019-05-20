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
    struct this *Left, *Right;
} Node, * NodePointer;

NodePointer Init() {
    return NULL;
}

NodePointer AddNode(NodePointer root, NodePointer newNode) {
    if (root == NULL) {
        return newNode;
    }

    if (newNode->Id < root->Id) {
        root->Left = AddNode(root->Left, newNode);
    } else {
        root->Right = AddNode(root->Right, newNode);
    } 

    return root;
}

NodePointer CreateNode(Key id) {
    NodePointer newNode = (NodePointer) malloc(sizeof(Node));
    newNode->Id = id;
    newNode->Left = NULL;
    newNode->Right = NULL;
    return newNode;
}

NodePointer Search(Key id, NodePointer root) {
    if (root == NULL) {
        return NULL;
    }

    if (root->Id == id) {
        return root;
    }

    if (root->Id > id) {
        return Search(id, root->Left);
    } else {
        return Search(id, root->Right);
    }
}

// Inorder traversal approach
int Count(NodePointer root) {
    if (!root) {
        return 0;
    }

    return Count(root->Left) 
            + 1 
            + Count(root->Right);
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

NodePointer SearchWithParent(NodePointer root, Key id, NodePointer *parentNode) {
    NodePointer currentNode = root;
    *parentNode = NULL;
    while (currentNode) {
        if (currentNode->Id == id) {
            return currentNode;
        }
        *parentNode = currentNode;
        if (id < currentNode->Id) {
            currentNode = currentNode->Left;
        } else {
            currentNode = currentNode->Right;
        }
    }
    return NULL;
}

NodePointer DeleteNode(NodePointer root, Key id) {
    NodePointer parentNode, currentNode, parentFromNodeToPromote, nodeToPromote;
    currentNode = SearchWithParent(root, id, &parentNode);

    if (currentNode == NULL) {
        return root;
    }

    if (!currentNode->Left || !currentNode->Right) {

        if (!currentNode->Left) {
            nodeToPromote = currentNode->Right;
        } else {
            nodeToPromote = currentNode->Left;
        }

    }
    else {

        parentFromNodeToPromote = currentNode;
        nodeToPromote = currentNode->Left;

        while(nodeToPromote->Right) {
            parentFromNodeToPromote = nodeToPromote;
            nodeToPromote = nodeToPromote->Right;
        }

        if (parentFromNodeToPromote != currentNode) {
            parentFromNodeToPromote->Right = nodeToPromote->Left;
            nodeToPromote->Left = currentNode->Left;
        }

        nodeToPromote->Right = currentNode->Right;
    }

    if (!parentNode) {
        free(currentNode);
        return nodeToPromote;
    }
    
    if (id < parentNode->Id) {
        parentNode->Left = nodeToPromote;
    } else {
        parentNode->Right = nodeToPromote;
    }

    free(currentNode);
    return root;
}


int main(void) {
    setlocale(LC_ALL, "");
    
    NodePointer root = Init();
    NodePointer newNode = CreateNode(23);
    root = AddNode(root, newNode);

    NodePointer newNode2 = CreateNode(12);
    root = AddNode(root, newNode2);
    
    NodePointer newNode3 = CreateNode(32);
    root = AddNode(root, newNode3);
    
    NodePointer newNode4 = CreateNode(44);
    root = AddNode(root, newNode4);
    
    NodePointer newNode5 = CreateNode(1);
    root = AddNode(root, newNode5);
    
    printf("%d\n", Count(root));
    ShowTree(root);
    printf("\n");

    root = DeleteNode(root, 32);

    printf("%d\n", Count(root));
    ShowTree(root);
    printf("\n");
    
    root = DeleteNode(root, 23);
    
    printf("%d\n", Count(root));
    ShowTree(root);
    printf("\n");
    
    system("PAUSE > NUL");
    return 0;
}