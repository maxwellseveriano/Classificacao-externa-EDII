#include <stdio.h>
#include <stdlib.h>

// Função para ler o arquivo binário e armazenar os valores em um vetor
int* lerArquivoBinario(const char *nomeArquivo, int *tam) {
    FILE *file = fopen(nomeArquivo, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        return NULL;
    }

    // Descobre o tamanho do arquivo
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Calcula o número de elementos no arquivo
    *tam = fileSize / sizeof(int);

    // Aloca memória para o vetor
    int *vetor = (int*)malloc(fileSize);
    if (vetor == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(file);
        return NULL;
    }

    // Lê o arquivo e armazena os valores no vetor
    fread(vetor, sizeof(int), *tam, file);

    fclose(file);
    return vetor;
}

// Função para imprimir o vetor
void printVetor(int *vetor, int tam) {
    for (int i = 0; i < tam; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main() {
    int tam;
    int *vetor = lerArquivoBinario("saida.bin", &tam);

    if (vetor != NULL) {
        printf("Vetor lido do arquivo binario:\n");
        printVetor(vetor, tam);
        free(vetor);
    }

    return 0;
}
