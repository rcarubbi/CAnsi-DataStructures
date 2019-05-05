#include <stdio.h>
#define alturaMaxima 225

typedef struct {
    int peso;
    int altura;
} PesoAltura;

int main(){

    PesoAltura pessoa1;
    pessoa1.peso = 80;
    pessoa1.altura = 285;
    printf("Peso %i, Altura %i. ", pessoa1.peso, pessoa1.altura);

    if (pessoa1.altura > alturaMaxima) {
        printf("Altura acima da maxima\n");
    } else {
        printf("Altura abaixo da maxima\n");
    }
    getchar();
    return 0;
}