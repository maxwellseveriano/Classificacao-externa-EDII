#include <stdio.h>
#include <stdlib.h>
#include "heapsort.h"

int qtd_particoes = 1;

void gera_nome_particao(char *nome_atual);

int main() {
    
    char f_nome[24] = "Particoes/particao0.bin";
    FILE *arquivo_saida = fopen("saida.bin", "wb");
    FILE *fp_particao[5];

    if (arquivo_saida == NULL){
        printf("Erro ao abrir o arquivo de saida \n");
        return 1;
    }

    HEAP heap;
    heap.nos = (NO *) malloc(5 * sizeof(NO));
    heap.tamanho = 0;

     printf("Imprimindo os primeiros clientes a serem ordenados na heap\n");
     printf("===================================================================\n");

    for (int i = 0; i < 5; i++){

        gera_nome_particao(f_nome);
        fp_particao[i] = fopen(f_nome, "rb");
        CLIENTE clientesIniciais;

        if(fp_particao[i] == NULL) {
            printf("ERRO ao abrir particao %d\n", i);
            exit(1);
    }

       

        if (fread(&clientesIniciais.CodigoCliente, sizeof(int), 1, fp_particao[i]) == 1){ 
        printf("Lido Cliente: %d\n", clientesIniciais.CodigoCliente); 
        NO nos = {clientesIniciais, i};
        heapSort(&heap, nos);
        for (int i = 0; i < heap.tamanho; i++) { 
        printf("Heap[%d]: %d\n", i, heap.nos[i].cliente.CodigoCliente); 
        }
        } else {
            if (feof(fp_particao[i])) {
                printf("Fim do arquivo alcançado para %s\n", f_nome);
            } else if (ferror(fp_particao[i])) {
                printf("Erro ao ler o arquivo %s\n", f_nome);
            }
        }
    }

     printf("===================================================================\n");


    NO noMin;
    noMin.indiceParticao = 1;

    printf("Escrevendo os clientes no arquivo: saida.bin\n");
    printf("===================================================================\n");

    while (heap.tamanho > 0){
        noMin = EscreverMenorElemento(&heap);
        fwrite(&noMin.cliente.CodigoCliente, sizeof(int), 1, arquivo_saida);
        printf("Escrevendo cliente no arquivo de saida: %d\n", noMin.cliente.CodigoCliente);


        CLIENTE clientesParaOrdenar;
        if (fread(&clientesParaOrdenar.CodigoCliente, sizeof (int), 1, fp_particao[noMin.indiceParticao]) == 1){
            NO no = {clientesParaOrdenar, noMin.indiceParticao};
            heapSort(&heap, no);
            
        }
    }

      printf("===================================================================\n");

    fechaArquivos(5, fp_particao);
    fclose(arquivo_saida);
    free(heap.nos);

return 0;
}

void gera_nome_particao(char *nome_atual) {
    nome_atual[18] = '0' + qtd_particoes;
    qtd_particoes++;
}