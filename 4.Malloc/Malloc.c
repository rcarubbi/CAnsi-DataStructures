#include <stdio.h>
#include <malloc.h>

int main() {
    int* pointer = (int*) malloc(sizeof(int));
    *pointer = 20;
    int intSize = sizeof(int);
    printf("*pointer=%i, intSize=%i\n", *pointer, intSize);
    getchar();
    return 0;
}