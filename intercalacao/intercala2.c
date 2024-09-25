#include<stdio.h>
#include<stdlib.h>

typedef struct No {
    int dado;
    struct No *esq;
    struct No *dir;
    struct No* pai;

    
} No;

No *criaRaiz(int dado) {

    No *no = (No*) malloc(sizeof(No));

    no->dado = dado;

    no->esq = NULL;
    no->dir = NULL;
    no->pai = NULL;

    return no;

}

void criaNoEsq(int dado, No *raiz) {

    if(raiz->esq == NULL) {
        raiz->esq = criaRaiz(dado);
        raiz->esq->pai = raiz;
    }

}

void criaNoDir(int dado, No *raiz) {

    if(raiz->dir == NULL) {
        raiz->dir = criaRaiz(dado);
        raiz->dir->pai = raiz;
    }

}


int main() {

    No *nozinho = criaRaiz(__INT_MAX__);
    criaNoDir(10, nozinho);
    criaNoEsq(5, nozinho);

    printf("%d\n", nozinho->dado);
    printf("%d\n", nozinho->esq->dado);
    printf("%d\n", nozinho->dir->dado);



}
