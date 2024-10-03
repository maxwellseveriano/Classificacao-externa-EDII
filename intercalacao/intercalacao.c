#include <stdio.h>
#include <stdlib.h>
#include "heapsort.h"

typedef struct Cliente {
    int codCliente;
    char nome[50];
    char data_nascimento[20];
} CLIENTE;


int qtd_particoes = 1;

void gera_nome_particao(char *nome_atual);

int main() {

    int jogadores[5];

    CLIENTE *cliente = (CLIENTE *)malloc(sizeof(CLIENTE)) ;
    
    char f_nome[24] = "Particoes/particao0.bin";
    FILE *arquivo_saida = fopen("saida.bin", "wb");
    FILE *fp_particao[5];

    if (arquivo_saida == NULL){
        printf("Erro ao abrir o arquivo de saida \n");
        return 1;
    }

    for (int i = 0; i < 5; i++){

        gera_nome_particao(f_nome);
        fp_particao[i] = fopen(f_nome, "rb");

        if(fp_particao == NULL) {
            exit(1);
    }

    fread(&jogadores[i], sizeof(int), 1, fp_particao[i]);
}

int tam = 5;

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

fclose(arquivo_saida);
return 0;
}

void gera_nome_particao(char *nome_atual) {
    nome_atual[18] = '0' + qtd_particoes;
    qtd_particoes++;
}