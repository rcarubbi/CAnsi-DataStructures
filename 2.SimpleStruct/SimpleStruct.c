#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#define MAX_HEIGHT 225

typedef struct {
    int Weight;
    int Height;
} Person;
 
int main(){
    setlocale(LC_ALL, "");
    Person person1;
    person1.Weight = 80;
    person1.Height = 285;
    printf("Peso %i, Altura %i. ", person1.Weight, person1.Height);

    if (person1.Height > MAX_HEIGHT) {
        printf("Altura acima da m�xima\n");
    } else {
        printf("Altura abaixo da m�xima\n");
    }
    system("Pause >> NULL");
    return 0;
}