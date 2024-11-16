#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Cliente {
    int codCliente;
    char nome[50];
    char data_nascimento[20];
} Cliente;

// Imprime cliente
void imprime(Cliente* func);

// Cria cliente. Lembrar de usar free(cliente)
Cliente* cliente(int cod, char* nome, char* data_nascimento);

// Salva cliente no arquivo out, na posicao atual do cursor
void salva(Cliente* func, FILE* out);

// Le um cliente do arquivo in na posicao atual do cursor
// Retorna um ponteiro para cliente lido do arquivo
Cliente* le(FILE* in);

// Retorna tamanho do cliente em bytes
int tamanho();

#endif