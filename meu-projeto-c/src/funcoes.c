#include <stdio.h>
#include "funcoes.h"

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* Limpa o que ficou digitado */
    }
}

int lerQuantidade(void) {
    int quantidade;

    while (1) {
        printf("Quantidade: ");
        if (scanf("%d", &quantidade) == 1 && quantidade > 0) {
            limparBuffer();
            return quantidade;
        }
        printf("Erro: a quantidade deve ser um inteiro maior que zero.\n");
        limparBuffer();
    }
}

float lerPrecoCompra(void) {
    float preco;

    while (1) {
        printf("Preco de compra (R$): ");
        if (scanf("%f", &preco) == 1 && preco > 0) {
            limparBuffer();
            return preco;
        }
        printf("Erro: o preco de compra deve ser maior que zero.\n");
        limparBuffer();
    }
}

float lerPrecoAtual(void) {
    float preco;

    while (1) {
        printf("Preco atual (R$): ");
        if (scanf("%f", &preco) == 1 && preco >= 0) {
            limparBuffer();
            return preco;
        }
        printf("Erro: o preco atual nao pode ser negativo.\n");
        limparBuffer();
    }
}

int cadastrarAtivo(Ativo carteira[], int qtdAtual) {
    if (qtdAtual >= MAX_ATIVOS) {
        printf("\nLimite maximo de ativos atingido (%d ativos)!\n", MAX_ATIVOS);
        return qtdAtual;
    }

    printf("\n--- Cadastro de Ativo ---\n");

    /* Le o nome e a categoria aceitando espacos e evitando ponto e virgula */
    printf("Nome (ex: PETR4, TESOURO SELIC): ");
    scanf(" %99[^\n;]", carteira[qtdAtual].nome);
    limparBuffer();

    printf("Categoria (ex: Acao, Renda Fixa): ");
    scanf(" %49[^\n;]", carteira[qtdAtual].categoria);
    limparBuffer();

    carteira[qtdAtual].quantidade  = lerQuantidade();
    carteira[qtdAtual].precoCompra = lerPrecoCompra();
    carteira[qtdAtual].precoAtual  = lerPrecoAtual();

    printf("\nAtivo cadastrado com sucesso!\n");
    return qtdAtual + 1;
}

float calcularRentabilidade(float precoCompra, float precoAtual) {
    if (precoCompra <= 0.0f) {
        return 0.0f;
    }
    return ((precoAtual - precoCompra) / precoCompra) * 100.0f;
}

float calcularLucroPrejuizo(float precoCompra, float precoAtual, int quantidade) {
    return (precoAtual - precoCompra) * quantidade;
}

float calcularValorTotal(const Ativo carteira[], int qtdAtual) {
    float total = 0.0f;
    int i;

    for (i = 0; i < qtdAtual; i++) {
        total += carteira[i].precoAtual * carteira[i].quantidade;
    }
    return total;
}

float calcularTotalInvestido(const Ativo carteira[], int qtdAtual) {
    float totalInvestido = 0.0f;
    int i;

    for (i = 0; i < qtdAtual; i++) {
        totalInvestido += carteira[i].precoCompra * carteira[i].quantidade;
    }
    return totalInvestido;
}

float calcularRentabilidadeGeral(const Ativo carteira[], int qtdAtual) {
    float totalInvestido = calcularTotalInvestido(carteira, qtdAtual);
    float valorTotalAtual = calcularValorTotal(carteira, qtdAtual);

    if (totalInvestido <= 0.0f) {
        return 0.0f;
    }
    return ((valorTotalAtual - totalInvestido) / totalInvestido) * 100.0f;
}

void listarCarteira(const Ativo carteira[], int qtdAtual) {
    int i;

    if (qtdAtual == 0) {
        printf("\nNenhum ativo cadastrado na carteira.\n");
        return;
    }

    printf("\n=== Carteira ===\n");
    for (i = 0; i < qtdAtual; i++) {
        float valorAtualAtivo = carteira[i].precoAtual * carteira[i].quantidade;
        float rentabilidadeAtivo = calcularRentabilidade(
            carteira[i].precoCompra,
            carteira[i].precoAtual
        );

        printf("%d. %s - %s - %d unidades - R$ %.2f\n",
               i + 1,
               carteira[i].nome,
               carteira[i].categoria,
               carteira[i].quantidade,
               carteira[i].precoAtual);
        printf("Valor atual: R$ %.2f\n", valorAtualAtivo);
        printf("Rentabilidade: %.2f%%\n\n", rentabilidadeAtivo);
    }

    printf("Valor total da carteira: R$ %.2f\n", calcularValorTotal(carteira, qtdAtual));
    printf("Rentabilidade geral: %.2f%%\n", calcularRentabilidadeGeral(carteira, qtdAtual));
}

void exibirValorTotal(const Ativo carteira[], int qtdAtual) {
    if (qtdAtual == 0) {
        printf("\nNenhum ativo cadastrado na carteira.\n");
        return;
    }

    printf("\n--- Valor Total da Carteira ---\n");
    printf("Total investido na compra: R$ %.2f\n", calcularTotalInvestido(carteira, qtdAtual));
    printf("Valor total da carteira: R$ %.2f\n", calcularValorTotal(carteira, qtdAtual));
}

void exibirRentabilidadeGeral(const Ativo carteira[], int qtdAtual) {
    float investido;
    float atual;
    float diferenca;
    float rentabilidadeGeral;

    if (qtdAtual == 0) {
        printf("\nNenhum ativo cadastrado na carteira.\n");
        return;
    }

    investido = calcularTotalInvestido(carteira, qtdAtual);
    atual = calcularValorTotal(carteira, qtdAtual);
    diferenca = atual - investido;
    rentabilidadeGeral = calcularRentabilidadeGeral(carteira, qtdAtual);

    printf("\n--- Rentabilidade Geral da Carteira ---\n");
    printf("Valor total investido: R$ %.2f\n", investido);
    printf("Valor total da carteira: R$ %.2f\n", atual);
    printf("Rentabilidade geral: %.2f%%\n", rentabilidadeGeral);

    if (diferenca > 0.0f) {
        printf("Resultado acumulado: Lucro de R$ %.2f\n", diferenca);
    } else if (diferenca < 0.0f) {
        printf("Resultado acumulado: Prejuizo de R$ %.2f\n", -diferenca);
    } else {
        printf("Resultado acumulado: R$ 0.00 (estavel)\n");
    }
}

void sair(void) {
    printf("\nObrigado por utilizar a Carteira de Investimentos!\n");
}