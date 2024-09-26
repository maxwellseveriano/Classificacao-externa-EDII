#include<stdio.h>
#include<stdlib.h>
#include "arvore.h"

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


