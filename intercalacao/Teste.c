#include <stdio.h>
#include <stdlib.h>

// Função para ler o arquivo binário e armazenar os valores em um vetor
int main() {

    FILE *arquivo_de_saida = fopen("saida.bin", "rb");

    int id;

    printf("Imprimindo código dos clientes no arquivo saida.bin\n");
    printf("==================================================================================================================================\n");
    while(fread(&id, sizeof(int), 1, arquivo_de_saida) > 0) {
        printf("%d ", id);
    }

    printf("\n");

     printf("==================================================================================================================================\n");

    return 0;
}