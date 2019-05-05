#include <stdio.h>

#define true 1
#define false 0
typedef int bool;

#define MAX 50

typedef int TIPOCHAVE;

typedef struct {
    TIPOCHAVE chave;
} REGISTRO;

typedef struct {
    REGISTRO A[MAX+1];
    int nroElem;
} LISTA;

void inicializarLista(LISTA* l) {
    l->nroElem = 0;
}

int tamanho(LISTA* l) {
    return l->nroElem;
}

void exibirLista(LISTA* l) {
    int i;
    printf("Lista: \" ");
    for(i=0;i<l->nroElem;i++){
        printf("%i ", l->A[i].chave);
    }
    printf("\"\n");
}

int buscaSentinela(LISTA* l, TIPOCHAVE ch) {
    int i = 0;
    l->A[l->nroElem].chave = ch;
    while(l->A[i].chave != ch) {
        i++;
    }

    if (i == l->nroElem) {
        return -1;
    } else {
        return i;
    }
}

bool inserirElemLista(LISTA* l, REGISTRO reg, int i) {
    int j;
    if ((l->nroElem == MAX) || (i<0) || (i > l->nroElem)){
        return false;
    }
    for(j = l->nroElem; j > i; j--) {
        l->A[j] = l->A[j-1];
    }
    l->A[i] = reg;
    l->nroElem++;
    return true;
}

bool excluirElemLista(LISTA* l, TIPOCHAVE ch)
{
    int pos, j;
    pos = buscaSentinela(l, ch);
    if (pos == -1) return false;
    for(j = pos; j < l->nroElem; j++) {
        l->A[j] = l->A[j+1];
    }
    l->nroElem--;
    return true;
}

void reinicializarLista(LISTA* l) {
    l->nroElem = 0;
}

int main() {
    LISTA lista;
    inicializarLista(&lista);
    exibirLista(&lista);
    printf("Numero de elementos na lista: %i.\n",tamanho(&lista));
    REGISTRO reg;
    reg.chave = 9;
    inserirElemLista(&lista,reg,0);
    exibirLista(&lista);
    reg.chave=3;
    inserirElemLista(&lista,reg,1);
    reg.chave=4;
    inserirElemLista(&lista,reg,2);
    reg.chave=1;
    inserirElemLista(&lista,reg,3);
    reg.chave=12;
    inserirElemLista(&lista,reg,2);
    exibirLista(&lista);
    printf("Numero de elementos na lista: %i.\n",tamanho(&lista));
 
    printf("Chave 4 encontrada na posicao: %i do arranjo A.\n",buscaSentinela(&lista,4));
  
    if (excluirElemLista(&lista,4)) printf("Exclusao bem sucedida: 4.\n");
    if (excluirElemLista(&lista,8)) printf("Exclusao bem sucedida: 8.\n");
    if (excluirElemLista(&lista,9)) printf("Exclusao bem sucedida: 9.\n");
    exibirLista(&lista);
    printf("Numero de elementos na lista: %i.\n",tamanho(&lista));
 
    reinicializarLista(&lista);
    exibirLista(&lista);
    printf("Numero de elementos na lista: %i.\n",tamanho(&lista));
 
    return 0;
}