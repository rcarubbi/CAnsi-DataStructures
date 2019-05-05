#include <stdio.h>

int main(){
    int number = 25;
    int* pointer = &number;
    *pointer = 30;
    printf("Valor atual de x: %i\n", number);
    getchar();
    return 0;
}