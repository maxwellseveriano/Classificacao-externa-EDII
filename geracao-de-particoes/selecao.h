#ifndef SELECAO_H
#define SELECAO_H

#include <stdlib.h>
#include <stdio.h>

void escreve_arquivo_entrada(FILE *fp, FILE *out);

int* le_registros(FILE *fp);

void selecao_por_substituicao(FILE *in);

int idice_menor(int *registros, int *congelados);

void gera_nome_particao(char *nome_atual);

int todos_congelados(int *registros_congelados);

void abre_nova_particao(FILE *fp_particao, char *nome);

void descongela(int *registros_congelados);

#endif