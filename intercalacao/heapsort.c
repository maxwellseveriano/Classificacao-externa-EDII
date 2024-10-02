#include<stdio.h>
#include<stdlib.h>
#include "heapsort.h"

void heapSort(int *vet, int tam){
    int i, aux;
    for (i = ((tam - 1) / 2); i >= 0; i--){
        criaHeap(vet, i, tam - 1);
    }
    for (i = (tam - 1); i >= 1; i--){
        aux = vet[0];
        vet[0] = vet [i];
        vet[i] = aux;
        criaHeap(vet, 0, (i - 1));
    }
}

void criaHeap(int *vet, int i, int finalVetor){
    int aux = vet[i];
    int filho = i * 2 + 1;
    while (filho <= finalVetor){
        if (filho < finalVetor){
            if (vet[filho] < vet[filho + 1]){
                filho = filho + 1;
            }
        }
        if (aux < vet[filho]){
            vet[i] = vet[filho];
            i = filho;
            filho = 2 * i + 1;
        }
        else{
            filho = finalVetor + 1;
        }
    }
    vet[i] = aux;
}

void EscreverMenorElemento(int *vet, int tam, FILE *arquivo_saida) {
    fwrite(&vet[0], sizeof(int), 1, arquivo_saida);
}

