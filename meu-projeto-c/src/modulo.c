#include <stdio.h>
#include "modulo.h"

int salvarCarteira(const Ativo carteira[], int qtdAtual) {
    FILE *arquivo;
    int i;

    /* Tenta abrir primeiro na pasta data/ conforme estrutura do projeto */
    arquivo = fopen(CAMINHO_ARQUIVO_DATA, "w");
    if (arquivo == NULL) {
        /* Caso a pasta data/ nao exista no diretorio atual, salva em carteira.txt */
        arquivo = fopen(CAMINHO_ARQUIVO_RAIZ, "w");
    }

    /* Verificacao obrigatoria de NULL ao abrir o arquivo */
    if (arquivo == NULL) {
        printf("\nErro: nao foi possivel abrir o arquivo carteira.txt para escrita.\n");
        return 0;
    }

    /* Percorre o vetor e escreve um ativo por linha separado por ponto e virgula */
    for (i = 0; i < qtdAtual; i++) {
        fprintf(arquivo, "%s;%s;%d;%.2f;%.2f\n",
                carteira[i].nome,
                carteira[i].categoria,
                carteira[i].quantidade,
                carteira[i].precoCompra,
                carteira[i].precoAtual);
    }

    fclose(arquivo);
    return 1;
}

int carregarCarteira(Ativo carteira[], int maxAtivos) {
    FILE *arquivo;
    int qtd = 0;

    /* Tenta abrir de data/carteira.txt ou, se nao encontrar, de carteira.txt */
    arquivo = fopen(CAMINHO_ARQUIVO_DATA, "r");
    if (arquivo == NULL) {
        arquivo = fopen(CAMINHO_ARQUIVO_RAIZ, "r");
    }

    /* Verificacao obrigatoria de NULL ao abrir o arquivo */
    if (arquivo == NULL) {
        /* Se o arquivo ainda nao existir, inicia a carteira vazia sem erro critico */
        return 0;
    }

    /* Le cada linha do arquivo respeitando espacos nos nomes e categorias */
    while (qtd < maxAtivos &&
           fscanf(arquivo, " %99[^;];%49[^;];%d;%f;%f",
                  carteira[qtd].nome,
                  carteira[qtd].categoria,
                  &carteira[qtd].quantidade,
                  &carteira[qtd].precoCompra,
                  &carteira[qtd].precoAtual) == 5) {
        qtd++;
    }

    fclose(arquivo);
    return qtd;
}