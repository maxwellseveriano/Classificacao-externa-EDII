#ifndef ARVORE_H
#define ARVORE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct No {
    int dado;
    struct No *esq;
    struct No *dir;
    struct No* pai;
    
} No;

No *criaRaiz(int dado);
void criaNoEsq(int dado, No *raiz);
void criaNoDir(int dado, No *raiz);


#endif
