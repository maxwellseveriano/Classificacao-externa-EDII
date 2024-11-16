#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "addclientes.h"
#include "indexacao.h"

int main() {
    FILE* A1;
    if ((A1 = fopen("A1.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    insere_clientes(A1);
    //le_clientes(A1);

    //Passo 1
    FILE* A2;
    if ((A2 = fopen("A2.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    passaAtributos(A1, A2);

    //Passo 2
    FILE* A3;
    if ((A3 = fopen("A3.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    separaAtributos(A2, A3);

    //Passo 3
    FILE* A4 = ordenaArquivo(A3, "A4.dat");

    //Passo 4
    FILE* A6 = geraArquivoIndice(A4, "A6.dat");

    //Passo 5
    FILE* A7 = ordenaPorChave(A6, "A7.dat");

    //Passo 6
    FILE* A8 = geraArqFinal(A1, A7, "A8.dat");

    fclose(A1);
    fclose(A2);
    fclose(A3);
    fclose(A4);
    fclose(A6);
    fclose(A7);
    fclose(A8);

    return 0;
}