#include<stdio.h>
#include<stdlib.h>
#include "heapsort.h"

void heapSort(HEAP *heap, NO nos){
    int i = heap->tamanho;
    heap->tamanho++;
    heap->nos[i] = nos;

    while (i != 0 && heap->nos [(i - 1) / 2].cliente.CodigoCliente > heap->nos[i].cliente.CodigoCliente){
        trocaNOS(&heap->nos[i], &heap->nos[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void criaHeap(HEAP *heap, int i){
    int filhoEsq = i * 2 + 1;
    int filhoDir = i * 2 + 2;
    int menor = i;
    
    if (filhoEsq < heap->tamanho && heap->nos[filhoEsq].cliente.CodigoCliente < heap->nos[menor].cliente.CodigoCliente){
        menor = filhoEsq;
    }
    if (filhoDir < heap->tamanho && heap->nos[filhoDir].cliente.CodigoCliente < heap->nos[menor].cliente.CodigoCliente){
        menor = filhoDir;
    }
    if (menor != i){    
        trocaNOS(&heap->nos[i], &heap->nos[menor]);
        criaHeap(heap, menor);
    }
}

NO EscreverMenorElemento(HEAP *heap) {
    NO topo = heap->nos[0];
    heap->nos[0] = heap->nos[heap->tamanho -1];
    heap->tamanho--;
    criaHeap(heap, 0);

    return topo;
}

void trocaNOS(NO *heapA, NO *heapB){
    NO aux;
    aux = *heapA;
    *heapA = *heapB;
    *heapB = aux;
}

void fechaArquivos(int tamanhoArquivo, FILE *arquivos[]){
    for (int i = 0; i < tamanhoArquivo ; i++) {
    fclose(arquivos[i]);
    }
}


