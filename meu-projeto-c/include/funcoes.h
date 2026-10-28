#ifndef FUNCOES_H
#define FUNCOES_H

#define MAX_ATIVOS 100

/* Estrutura que representa um ativo financeiro da carteira */
typedef struct Ativo {
    char nome[100];
    char categoria[50];
    int quantidade;
    float precoCompra;
    float precoAtual;
} Ativo;

/* Limpa o que ficou digitado no buffer do teclado */
void limparBuffer(void);

/* Le e valida a quantidade e os precos digitados pelo usuario */
int lerQuantidade(void);
float lerPrecoCompra(void);
float lerPrecoAtual(void);

/* Cadastra um novo ativo no vetor da carteira e retorna a nova quantidade */
int cadastrarAtivo(Ativo carteira[], int qtdAtual);

/* Lista todos os ativos cadastrados na carteira */
void listarCarteira(const Ativo carteira[], int qtdAtual);

/* Calcula a rentabilidade percentual de um unico ativo */
float calcularRentabilidade(float precoCompra, float precoAtual);

/* Calcula o lucro ou o prejuizo em reais de um ativo */
float calcularLucroPrejuizo(float precoCompra, float precoAtual, int quantidade);

/* Calcula o valor total atual acumulado na carteira */
float calcularValorTotal(const Ativo carteira[], int qtdAtual);

/* Calcula o valor total investido (preco de compra * quantidade) na carteira */
float calcularTotalInvestido(const Ativo carteira[], int qtdAtual);

/* Calcula a rentabilidade percentual geral de toda a carteira */
float calcularRentabilidadeGeral(const Ativo carteira[], int qtdAtual);

/* Exibe o resumo do valor total da carteira */
void exibirValorTotal(const Ativo carteira[], int qtdAtual);

/* Exibe o resumo da rentabilidade geral da carteira */
void exibirRentabilidadeGeral(const Ativo carteira[], int qtdAtual);

/* Mostra a mensagem de despedida */
void sair(void);

#endif