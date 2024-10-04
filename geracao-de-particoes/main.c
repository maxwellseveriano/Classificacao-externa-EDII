#include <stdio.h>
#include <stdlib.h>
#include "selecao.h"
#include "cliente.h"
#include "addclientes.h"

#define M 7

int registros = 0;
int qtd_registros;
int qtd_particoes = 1;

void escreve_arquivo_entrada(FILE *fp, FILE *out) {
    int numeros[QTD_CLIENTES];
    Cliente *cliente;

    rewind(out);
    for (int i = 0; i < QTD_CLIENTES; i++) {
        cliente = le(out);
        fwrite(&cliente->codCliente, sizeof(int), 1, fp);
        free(cliente);
    }
    rewind(fp);
}

int* le_registros(FILE *fp) {
    int *regs = (int*) malloc(sizeof(int) * M);
    qtd_registros = fread(regs, sizeof(int), M, fp);
    return regs;
}

void selecao_por_substituicao(FILE *in) {
    int *registros_atuais = le_registros(in);
    int registros_congelados[M] = {0};
    char f_nome[24] = "Particoes/particao0.bin";

    gera_nome_particao(f_nome);
    FILE *fp_particao = fopen(f_nome, "w+b");
    
    if (fp_particao == NULL) {
        printf("Falha ao criar uma particao\n");
        exit(1);
    }
    int novo_registro;
    int indice_do_menor = idice_menor(registros_atuais, registros_congelados);
    int menor_registro = registros_atuais[indice_do_menor];
    
    fread(&novo_registro, sizeof(int), 1, in);
    fwrite(&menor_registro, sizeof(int), 1, fp_particao);
    int ultimo_registro = menor_registro;
    
    registros_atuais[indice_do_menor] = novo_registro;
    int adcionouNaParticao = 1;
    int novaParticao = 0;
    int acabouLeitura = 0;
    
    while (!todos_congelados(registros_congelados) || !acabouLeitura) {
        if (adcionouNaParticao && !acabouLeitura) {
            registros_atuais[indice_do_menor] = novo_registro;
            if (fread(&novo_registro, sizeof(int), 1, in) <= 0) {
                acabouLeitura = 1;
            }
            
        }
        if (todos_congelados(registros_congelados)) {
            abre_nova_particao(fp_particao, f_nome);
            descongela(registros_congelados);
            novaParticao = 1;
        }

        indice_do_menor = idice_menor(registros_atuais, registros_congelados);
        menor_registro = registros_atuais[indice_do_menor];

        if ((menor_registro < ultimo_registro) && !novaParticao) {
            registros_congelados[indice_do_menor] = 1;
            adcionouNaParticao = 0;
        }
        else {
            if (acabouLeitura) {
                registros_congelados[indice_do_menor] = -1;
            }
            fwrite(&menor_registro, sizeof(int), 1,  fp_particao);
            ultimo_registro = menor_registro;
            adcionouNaParticao = 1;
            novaParticao = 0;
        }
    }
    descongela(registros_congelados);

    if (!todos_congelados(registros_congelados)) {
        abre_nova_particao(fp_particao, f_nome);
    }

    while (!todos_congelados(registros_congelados)) {
        indice_do_menor = idice_menor(registros_atuais, registros_congelados);
        menor_registro = registros_atuais[indice_do_menor];

        fwrite(&menor_registro, sizeof(int), 1,  fp_particao);
        registros_congelados[indice_do_menor] = -1;
    }
}

int idice_menor(int *registros, int *congelados) {
    int i, menor = __INT_MAX__, indiceMenor;

    for(i = 0; i < qtd_registros; i++) {
        if (registros[i] < menor && congelados[i] == 0) {
            menor = registros[i];
            indiceMenor = i;
        }
    }
    return indiceMenor;
}

void gera_nome_particao(char *nome_atual) {
    nome_atual[18] = '0' + qtd_particoes;
    qtd_particoes++;
}

int todos_congelados(int *registros_congelados) {
    int i;
    for(i = 0; i < M; i++) {
        if (registros_congelados[i] == 0) return 0;
    }
    return 1;
}

void descongela(int *registros_congelados) {
    int i;
    for(i = 0; i < M; i++) {
        if (registros_congelados[i] == 1)
            registros_congelados[i] = 0;
    }
}

void abre_nova_particao(FILE *fp_particao, char *nome) {
    fclose(fp_particao);

    gera_nome_particao(nome);
    fp_particao = fopen(nome, "w+");
    
    if (fp_particao == NULL) {
        printf("Falha ao criar uma particao\n");
        exit(1);
    }
}

int main() {

    FILE *clientes_dat;
    if ((clientes_dat = fopen("cliente.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    insere_clientes(clientes_dat);
    le_clientes(clientes_dat);

    FILE *fp = fopen("entrada.dat", "w+b");

    if (fp == NULL) {
        printf("Falha ao abrir o arquivo\n");
        exit(1);
    }
    
    escreve_arquivo_entrada(fp, clientes_dat);

    selecao_por_substituicao(fp);

    fclose(fp);
    fclose(clientes_dat);

    return 0;
}