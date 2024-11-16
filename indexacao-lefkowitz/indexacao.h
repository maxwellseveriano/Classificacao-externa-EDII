#ifndef INDEXACAO_H
#define INDEXACAO_H

#include <stdlib.h>
#include <stdio.h>
#include "cliente.h"
#include "addclientes.h"

typedef struct {
    int EndDisc;
    int codCliente;
    int idade;
} ClienteIndex;

void passaAtributos(FILE* in, FILE* out);

void separaAtributos(FILE* in, FILE* out);

FILE* ordenaArquivo(FILE* in, char* nomeArq);

FILE* geraArquivoIndice(FILE* in, char* nomeArq);

FILE* ordenaPorChave(FILE* in, char* nomeArq);

FILE* geraArqFinal(FILE* fp1, FILE* fp2, char* nomeArq);

#endif