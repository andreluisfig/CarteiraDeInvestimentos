#ifndef MODULO_H
#define MODULO_H

#include "funcoes.h"

/* Caminhos padrao para o arquivo de persistencia */
#define CAMINHO_ARQUIVO_DATA "data/carteira.txt"
#define CAMINHO_ARQUIVO_RAIZ "carteira.txt"

/* Salva todos os ativos do vetor no arquivo carteira.txt.
 * Retorna 1 em caso de sucesso e 0 em caso de erro. */
int salvarCarteira(const Ativo carteira[], int qtdAtual);

/* Carrega os ativos do arquivo carteira.txt para o vetor.
 * Retorna a quantidade de ativos carregados. */
int carregarCarteira(Ativo carteira[], int maxAtivos);

#endif