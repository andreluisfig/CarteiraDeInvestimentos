#include <stdio.h>
#include "funcoes.h"
#include "modulo.h"

int main(void) {
    Ativo carteira[MAX_ATIVOS];
    int qtdAtivos = 0;
    int opcao = 0;

    /* Recarrega os ativos salvos em carteira.txt ao iniciar o programa */
    qtdAtivos = carregarCarteira(carteira, MAX_ATIVOS);
    if (qtdAtivos > 0) {
        printf("Carteira carregada com sucesso (%d ativo(s) encontrado(s)).\n", qtdAtivos);
    }

    /* O menu se repete ate o usuario escolher 5 (Sair) */
    while (opcao != 5) {
        printf("\n=== Carteira de Investimentos ===\n");
        printf("1. Cadastrar ativo\n");
        printf("2. Listar carteira\n");
        printf("3. Calcular valor total\n");
        printf("4. Calcular rentabilidade geral\n");
        printf("5. Sair\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\nDigite uma opcao numerica valida.\n");
            limparBuffer();
            continue;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                qtdAtivos = cadastrarAtivo(carteira, qtdAtivos);
                salvarCarteira(carteira, qtdAtivos);
                break;

            case 2:
                listarCarteira(carteira, qtdAtivos);
                break;

            case 3:
                exibirValorTotal(carteira, qtdAtivos);
                break;

            case 4:
                exibirRentabilidadeGeral(carteira, qtdAtivos);
                break;

            case 5:
                if (salvarCarteira(carteira, qtdAtivos)) {
                    printf("\nDados salvos com sucesso em carteira.txt!\n");
                }
                sair();
                break;

            default:
                printf("\nOpcao invalida. Escolha de 1 a 5.\n");
                break;
        }
    }

    return 0;
}