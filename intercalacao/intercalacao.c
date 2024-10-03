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

        gera_nome_particao(f_nome);
        fp_particao[i] = fopen(f_nome, "rb");
        CLIENTE leonardo;

        if(fp_particao == NULL) {
            exit(1);
    }

    if (fread(&leonardo, sizeof(CLIENTE), 1, fp_particao[i]) >= 1){
        NO nos = {leonardo, i};
        heapSort(&heap, nos);
    }
}

/*
heapSort(jogadores, tam);

while (tam > 0){
    EscreverMenorElemento(jogadores, tam, arquivo_saida);

    int MenorIndice = 0;
    for(int i = 1; i < tam; i++) {
        if (jogadores[i] < jogadores[MenorIndice]){
            MenorIndice = i;
        }
    }

    if (fread(&jogadores[MenorIndice], sizeof(int), 1, fp_particao[MenorIndice]) == 0){
        fclose(fp_particao[MenorIndice]);
        for (int i = MenorIndice; i < tam -1; i++){
            jogadores[i] = jogadores[i + 1];
            fp_particao[i] = fp_particao[i + 1];
        }
        tam--;
    }
    heapSort(jogadores,tam);
}
*/

while (heap.tamanho > 0){
    NO noMin = EscreverMenorElemento(&heap);
    fwrite(&noMin.cliente, sizeof(CLIENTE), 1, arquivo_saida);
    CLIENTE leticia;
    if (fread(&leticia, sizeof (leticia), 1, fp_particao[noMin.indiceParticao]) >= 1){
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