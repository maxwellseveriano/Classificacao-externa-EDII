#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int CodigoCliente;
    char nome[50];
    char DataNascimento[20];
}CLIENTE;

typedef struct {
    CLIENTE cliente;
    int indiceParticao;
}NO;

typedef struct {
    NO *nos;
    int tamanho;
}HEAP;

void heapSort(HEAP *heap, NO nos);
void criaHeap(HEAP *heap, int i);
NO EscreverMenorElemento(HEAP *heap);
void trocaNOS (NO *heapA, NO *heapB);
void fechaArquivos(int tamanhoArquivo, FILE *arquivos[]);


#endif


