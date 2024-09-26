#include <stdio.h>
#include<stdlib.h>
#include "arvore.h"

typedef struct Cliente {
    int codCliente;
    char nome[50];
    char data_nascimento[20];
} CLIENTE;


int qtd_particoes = 1;

void gera_nome_particao(char *nome_atual);
int arvore_de_vencedores(int jogadores[], int arvore[], int n);

int main() {

    int vencedor = 0, menor = 0;
    No *aux; 

    int jogadores[100], folhas[100];

    CLIENTE *cliente = (CLIENTE *)malloc(sizeof(CLIENTE)) ;
    
    char f_nome[24] = "Particoes/particao0.bin";
    for (int i = 0; i < 5; i++){

        gera_nome_particao(f_nome);
        FILE *fp_particao = fopen(f_nome, "rb");

        if(fp_particao == NULL) {
            exit(1);
    }

    printf("Valores lido do arquivo %s: \n", f_nome);

    fread(&jogadores[i], sizeof(int), 1, fp_particao);
    fclose(fp_particao);


    // while(fread(&cliente->codCliente, sizeof(int), 1, fp_particao)) {

    //     printf("%d\n", cliente->codCliente);
        
    // }
}

 for(int i = 0; i< 4; i++) {
     if(jogadores[i] < jogadores[i + 1]) {
        menor = jogadores[i];
        aux = criaRaiz(menor); 
        criaNoEsq(menor, aux);
        criaNoDir(jogadores[i+1], aux);
     }

     else if  (jogadores[i+1] < jogadores[i]){
        menor = jogadores[i+1];
        aux = criaRaiz(menor); 
        criaNoEsq(menor, aux);
        criaNoDir(jogadores[i], aux);
     }
     i++;

    printf("%d\n", aux->dado);
    printf("%d\n", aux->esq->dado);
    printf("%d\n", aux->dir->dado);
    printf("-------------------\n");
 }

aux = criaRaiz(jogadores[4]);
printf("%d", aux->dado);


}
/*int arvore_de_vencedores(int jogadores[], int folhas[], int n) {

    int l = 0;
    int vencedor[50];

    for(int i = 0; i< n; i++) {

        folhas[n + i] = jogadores[i];

    }
    for(int j = 0; j < n; j++) { //Na arvore os jogadores estão ocupando o nó folha, então o for começa de n e vai té 2n. as posições de 5 a 9

        folhas[j] = __INT_MAX__; //Inicializa um valor gigante nos outros nós para que eles nunca sejam maiores
    }


    for(int k = (2 * n) - 1; k > 0; k--) {
        folhas[k-1] = (folhas[k] < folhas[k - 1] ? folhas[k] : folhas[k - 1]);
    }
    

    return folhas[0];

} */

void gera_nome_particao(char *nome_atual) {
    nome_atual[18] = '0' + qtd_particoes;
    qtd_particoes++;
}