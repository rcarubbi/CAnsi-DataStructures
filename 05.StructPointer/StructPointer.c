#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>

#define MAX_HEIGHT 225

typedef struct {
    int Weight;
    int Height;
} Person;

int main(){
    setlocale(LC_ALL, "");
    
    Person* person1 = (Person*) malloc(sizeof(Person));
    person1->Weight = 80;
    person1->Height = 285;
    printf("Peso %i, Altura %i. ", person1->Weight, person1->Height);

    if (person1->Height > MAX_HEIGHT) {
        printf("Altura acima da máxima\n");
    } else {
        printf("Altura abaixo da máxima\n");
    }
    system("PAUSE > NUL");
    return 0;
}