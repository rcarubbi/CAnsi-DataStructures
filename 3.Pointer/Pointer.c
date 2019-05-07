#include <stdio.h>
#include <stdlib.h>

int main(){
    int number = 25;
    int* pointer = &number;
    *pointer = 30;
    printf("Valor atual de x: %i\n", number);
    system("Pause >> NULL");
    return 0;
}