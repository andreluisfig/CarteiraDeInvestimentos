#ifndef FUNCOES_H
#define FUNCOES_H

#define MAX_ATIVOS 100

/* Taxas mensais ilustrativas para o Simulador Educativo (em formato decimal) */
#define TAXA_POUPANCA      0.005  /* 0.50% ao mes */
#define TAXA_TESOURO_SELIC 0.008  /* 0.80% ao mes */
#define TAXA_CDB_110_CDI   0.009  /* 0.90% ao mes */
#define MESES_SIMULACAO    12

/* Estrutura que representa um ativo financeiro da carteira */
typedef struct Ativo {
    char nome[100];
    char categoria[50];
    int quantidade;
    double precoCompra;
    double precoAtual;
} Ativo;

/* Limpa o que ficou digitado no buffer do teclado */
void limparBuffer(void);

/* Encerra o programa com mensagem quando a entrada acaba (Ctrl+Z / Ctrl+D) */
void encerrarPorFimDeEntrada(void);

/* Le uma linha de texto nao vazia e sem ';' (usada para nome e categoria) */
void lerTexto(const char *rotulo, char destino[], int tamanho);

/* Le e valida a quantidade e os precos digitados pelo usuario */
int lerQuantidade(void);
double lerPrecoCompra(void);
double lerPrecoAtual(void);

/* 1. Cadastra um novo ativo no vetor da carteira e retorna a nova quantidade */
int cadastrarAtivo(Ativo carteira[], int qtdAtual);

/* 2. Lista todos os ativos cadastrados na carteira */
void listarCarteira(const Ativo carteira[], int qtdAtual);

/* Funcoes auxiliares de calculo financeiro */
double calcularRentabilidade(double precoCompra, double precoAtual);
double calcularLucroPrejuizo(double precoCompra, double precoAtual, int quantidade);
double calcularValorTotal(const Ativo carteira[], int qtdAtual);
double calcularTotalInvestido(const Ativo carteira[], int qtdAtual);
double calcularLucroPrejuizoTotal(const Ativo carteira[], int qtdAtual);
double calcularRentabilidadeGeral(const Ativo carteira[], int qtdAtual);

/* 3. Exibe o resumo do valor total da carteira */
void exibirValorTotal(const Ativo carteira[], int qtdAtual);

/* 4. Exibe o resumo da rentabilidade geral da carteira */
void exibirRentabilidadeGeral(const Ativo carteira[], int qtdAtual);

/* 5. Ordena a carteira por rentabilidade (do melhor para o pior - Bubble Sort) */
void ordenarPorRentabilidade(Ativo carteira[], int qtdAtual);

/* 6. Simulador educativo comparando Poupanca, Tesouro Selic e CDB por 12 meses */
void executarSimuladorEducativo(const Ativo carteira[], int qtdAtual);

/* 7. Exibe o relatorio final completo com ativos ordenados e impacto social (ODS 8.10) */
void exibirRelatorioFinal(Ativo carteira[], int qtdAtual);

/* 0. Mostra a mensagem de despedida */
void sair(void);

#endif
