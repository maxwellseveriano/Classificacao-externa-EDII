#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <stdlib.h>
#include <stdio.h>

void heapSort(int *vet, int tam);
void criaHeap(int *vet, int i, int finalVetor);
void EscreverMenorElemento(int *vet, int tam, FILE *arquivo_saida);


#endif


