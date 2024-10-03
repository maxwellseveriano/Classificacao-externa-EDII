#include <stdio.h>
#include <stdlib.h>
#include "heapsort.h"

int qtd_particoes = 1;

void gera_nome_particao(char *nome_atual);

int main() {

    CLIENTE *cliente = (CLIENTE *)malloc(sizeof(CLIENTE)) ;
    
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

    for (int i = 0; i < 5; i++){
        printf("OK \n");
        gera_nome_particao(f_nome);
        fp_particao[i] = fopen(f_nome, "rb");
        CLIENTE leonardo;
        printf("OKTWO ");
        if(fp_particao[i] == NULL) {
            printf("ERRO ao abrir particao %d\n", i);
            exit(1);
    }

        if (fread(&leonardo, sizeof(CLIENTE), 1, fp_particao[i]) <= 1){ 
        printf("Lido Cliente: %d\n", leonardo.CodigoCliente); //debug
        NO nos = {leonardo, i};
        heapSort(&heap, nos);
        for (int i = 0; i < heap.tamanho; i++) { //debug
        printf("Heap[%d]: %d\n", i, heap.nos[i].cliente.CodigoCliente); //debug
        }
        } else {
            if (feof(fp_particao[i])) {
                printf("Fim do arquivo alcançado para %s\n", f_nome);
            } else if (ferror(fp_particao[i])) {
                printf("Erro ao ler o arquivo %s\n", f_nome);
            }
        }
    }


    while (heap.tamanho > 0){
        NO noMin = EscreverMenorElemento(&heap);
        fwrite(&noMin.cliente, sizeof(CLIENTE), 1, arquivo_saida);
        printf("Escrevendo cliente no arquivo de saida: %d\n", noMin.cliente.CodigoCliente); // Debug

        CLIENTE leticia;
        if (fread(&leticia, sizeof (leticia), 1, fp_particao[noMin.indiceParticao]) >= 1){
            printf("Lido Cliente: %d\n", leticia.CodigoCliente); //debug
            NO no = {leticia, noMin.indiceParticao};
            heapSort(&heap, no);
        }
    }

    fechaArquivos(5, fp_particao);
    fclose(arquivo_saida);
    free(heap.nos);

return 0;
}

void gera_nome_particao(char *nome_atual) {
    nome_atual[18] = '0' + qtd_particoes;
    qtd_particoes++;
}