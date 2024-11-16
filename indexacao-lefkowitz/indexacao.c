#include <stdlib.h>
#include <stdio.h>
#include "cliente.h"
#include "addclientes.h"
#include "indexacao.h"

void passaAtributos(FILE* in, FILE* out) {
    rewind(in);
    Cliente* c;
    ClienteIndex ci;
    int ED = 1; //Endereço de Disco
    while ((c = le(in)) != NULL) {
        fwrite(&ED, sizeof(int), 1, out);
        fwrite(&c->codCliente, sizeof(int), 1, out);
        fwrite(&c->idade, sizeof(int), 1, out);
        ED++;
        free(c);
    }
}

void separaAtributos(FILE* in, FILE* out) {
    rewind(in);
    Cliente* c;
    ClienteIndex ci;
    while (fread(&ci, sizeof(ClienteIndex), 1, in) > 0) {
        fwrite(&ci.EndDisc, sizeof(int), 1, out);
        fwrite(&ci.codCliente, sizeof(int), 1, out);
        fwrite(&ci.idade, sizeof(int), 1, out);
        free(c);
    }
}

FILE* ordenaArquivo(FILE* in, char* nomeArq) {
    rewind(in);
    ClienteIndex clientes[QTD_CLIENTES], aux;

    for (int i = 0; i < QTD_CLIENTES; i++) {
        fread(&clientes[i], sizeof(ClienteIndex), 1, in);
    }
    for (int i = 0; i < QTD_CLIENTES - 1; i++) {
        for (int j = 0; j < QTD_CLIENTES - i - 1; j++) {
            if (clientes[j].idade > clientes[j + 1].idade) {
                aux = clientes[j];
                clientes[j] = clientes[j + 1];
                clientes[j + 1] = aux;
            }
        }
    }
    FILE* out;
    if ((out = fopen(nomeArq, "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    for (int i = 0; i < QTD_CLIENTES; i++) {
        fwrite(&clientes[i], sizeof(ClienteIndex), 1, out);
    }

    return out;
}

FILE* geraArquivoIndice(FILE* in, char* nomeArq) {
    rewind(in);
    int qtdAtual = 0, total = 1, fim = 0, prox;
    ClienteIndex primeiroCliente, novoCliente;
    fread(&primeiroCliente, sizeof(ClienteIndex), 1, in);

    FILE* A5, * A6;
    if ((A5 = fopen("A5.dat", "w+b")) == NULL || (A6 = fopen(nomeArq, "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    fwrite(&primeiroCliente, sizeof(ClienteIndex), 1, A6);

    for (int i = 1; i <= QTD_CLIENTES; i++) {
        if (i < QTD_CLIENTES) fread(&novoCliente, sizeof(ClienteIndex), 1, in);

        if (novoCliente.idade != primeiroCliente.idade || i == QTD_CLIENTES) {
            fwrite(&primeiroCliente.idade, sizeof(int), 1, A5);
            fwrite(&primeiroCliente.EndDisc, sizeof(int), 1, A5);
            fwrite(&total, sizeof(int), 1, A5);

            primeiroCliente = novoCliente;
            total = 1;
            prox = -1;
        }
        else {
            total++;
            prox = novoCliente.EndDisc;
        }
        fwrite(&prox, sizeof(int), 1, A6);
        if (i < QTD_CLIENTES) fwrite(&novoCliente, sizeof(ClienteIndex), 1, A6);
    }
    return A6;
}

FILE* ordenaPorChave(FILE* in, char* nomeArq) {
    rewind(in);
    ClienteIndex clientes[QTD_CLIENTES], auxCliente;
    int proxs[QTD_CLIENTES], auxProx;

    for (int i = 0; i < QTD_CLIENTES; i++) {
        fread(&clientes[i], sizeof(ClienteIndex), 1, in);
        fread(&proxs[i], sizeof(int), 1, in);
    }
    for (int i = 0; i < QTD_CLIENTES - 1; i++) {
        for (int j = 0; j < QTD_CLIENTES - i - 1; j++) {
            if (clientes[j].codCliente > clientes[j + 1].codCliente) {
                auxCliente = clientes[j];
                clientes[j] = clientes[j + 1];
                clientes[j + 1] = auxCliente;

                auxProx = proxs[j];
                proxs[j] = proxs[j + 1];
                proxs[j + 1] = auxProx;
            }
        }
    }
    FILE* out;
    if ((out = fopen(nomeArq, "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    for (int i = 0; i < QTD_CLIENTES; i++) {
        fwrite(&clientes[i], sizeof(ClienteIndex), 1, out);
        fwrite(&proxs[i], sizeof(int), 1, out);
    }

    return out;
}

FILE* geraArqFinal(FILE* fp1, FILE* fp2, char* nomeArq) {
    rewind(fp1); rewind(fp2);
    int prox;

    FILE* out;
    if ((out = fopen(nomeArq, "w+b")) == NULL || fp1 == NULL || fp2 == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    Cliente* clienteA1;
    ClienteIndex a;
    while ((clienteA1 = le(fp1)) != NULL) {
        fseek(fp2, sizeof(ClienteIndex), SEEK_CUR);
        //fread(&a, sizeof(a), 1, fp2);
        fread(&prox, sizeof(int), 1, fp2);

        fwrite(&clienteA1->codCliente, sizeof(int), 1, out);
        fwrite(clienteA1->nome, sizeof(char), sizeof(clienteA1->nome), out);
        fwrite(&clienteA1->idade, sizeof(int), 1, out);
        fwrite(&prox, sizeof(int), 1, out);

        free(clienteA1);
    }rewind(out);
    while ((clienteA1 = le(out)) != NULL) {
        fread(&prox, sizeof(int), 1, out);

        printf("%d %s %d %d\n", clienteA1->codCliente, clienteA1->nome, clienteA1->idade, prox);
        free(clienteA1);
    }
    return out;
}