#include <stdlib.h>
#include <stdio.h>
#include "addclientes.h"
#include "cliente.h"

#define QTD_CLIENTES 50

void insere_clientes(FILE* out) {
    Cliente* clientes[QTD_CLIENTES];

    char* nomes[50] = {
   "João", "Maria", "Pedro", "Ana", "Paulo", "Carla", "Ricardo", "Fernanda",
   "Lucas", "Juliana", "Leonardo", "Bianca", "Felipe", "Camila", "Bruno",
   "Mariana", "Thiago", "Eduarda", "André", "Letícia", "Rodrigo", "Patrícia",
   "Sérgio", "Cristina", "Maurício", "Vera", "Vinícius", "Sabrina", "Rafael",
   "Marta", "Guilherme", "Natália", "Daniel", "Larissa", "Rogério", "Isabela",
   "Gustavo", "Caroline", "Fábio", "Aline", "Marcelo", "Roberta", "Alexandre",
   "Renata", "Diego", "Lúcia", "Roberto", "Flávia", "Antônio", "Helena"
    };

    // Vetor com 50 datas de nascimento
    int idades[50] = {
        38, 69, 69, 28, 11, 55, 45, 23, 16, 70, 35,
        27, 23, 26, 10, 40, 72, 72, 28, 49, 49, 25,
        20, 65, 71, 39, 28, 65, 26, 27, 39, 70, 39,
        27, 31, 31, 23, 49, 37, 23, 57, 71, 25, 65,
        17, 50, 14, 34, 35, 11
    };

    // Vetor com 50 IDs fora de ordem
    int codClientes[50] = {
        35, 3, 27, 49, 12, 7, 18, 50, 42, 15,
        1, 31, 19, 23, 9, 24, 4, 36, 46, 14,
        22, 10, 32, 30, 43, 11, 16, 48, 26, 20,
        34, 21, 45, 38, 13, 17, 47, 6, 25, 5,
        2, 28, 39, 29, 44, 40, 41, 33, 8, 37
    };

    Cliente* novo_cliente;

    for (int i = 0; i < QTD_CLIENTES; i++) {
        novo_cliente = cliente(i + 1, nomes[i], idades[i]);
        salva(novo_cliente, out);
        free(novo_cliente);
    }
}

void le_clientes(FILE* in) {
    printf("\n\nLendo funcionários do arquivo...\n\n");
    rewind(in);
    Cliente* f;
    while ((f = le(in)) != NULL) {
        imprime(f);
        free(f);
    }
}