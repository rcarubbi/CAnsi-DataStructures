#include <stdio.h>
#include <malloc.h>

#define MAX_HEIGHT 225

typedef struct {
    int Weight;
    int Height;
} Person;

int main(){

    Person* person1 = (Person*) malloc(sizeof(Person));
    person1->Weight = 80;
    person1->Height = 285;
    printf("Peso %i, Altura %i. ", person1->Weight, person1->Height);

    if (person1->Height > MAX_HEIGHT) {
        printf("Altura acima da maxima\n");
    } else {
        printf("Altura abaixo da maxima\n");
    }
    getchar();
    return 0;
}