#include <stdio.h>
#include "funcoes.h"
#include "modulo.h"

int main(void) {
    Ativo carteira[MAX_ATIVOS];
    int qtdAtivos = 0;
    int opcao = -1;
    int leitura;

    /* Recarrega os ativos salvos em data/carteira.txt ao iniciar o programa */
    qtdAtivos = carregarCarteira(carteira, MAX_ATIVOS);
    if (qtdAtivos > 0) {
        printf("Carteira carregada com sucesso (%d ativo(s) encontrado(s)).\n", qtdAtivos);
    }

    /* O menu se repete ate o usuario escolher 8 (Sair) */
    while (opcao != 8) {
        printf("\n=== CARTEIRA DE INVESTIMENTOS ===\n");
        printf("1. Cadastrar ativo\n");
        printf("2. Listar ativos\n");
        printf("3. Valor total da carteira\n");
        printf("4. Rentabilidade geral\n");
        printf("5. Ordenar por rentabilidade\n");
        printf("6. Simulador educativo\n");
        printf("7. Relatorio final\n");
        printf("8. Sair\n");
        printf("Opcao: ");

        leitura = scanf("%d", &opcao);
        if (leitura == EOF) {
            /* Entrada encerrada (Ctrl+Z / Ctrl+D): salva e sai em vez de repetir o menu */
            salvarCarteira(carteira, qtdAtivos);
            sair();
            break;
        }
        if (leitura != 1) {
            printf("\nDigite uma opcao numerica valida (1 a 8).\n");
            limparBuffer();
            opcao = -1;
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
                if (qtdAtivos == 0) {
                    printf("\nNenhum ativo cadastrado para ordenar.\n");
                } else {
                    ordenarPorRentabilidade(carteira, qtdAtivos);
                    salvarCarteira(carteira, qtdAtivos);
                    printf("\nCarteira ordenada por rentabilidade (do melhor para o pior desempenho)!\n");
                    listarCarteira(carteira, qtdAtivos);
                }
                break;

            case 6:
                executarSimuladorEducativo(carteira, qtdAtivos);
                break;

            case 7:
                exibirRelatorioFinal(carteira, qtdAtivos);
                salvarCarteira(carteira, qtdAtivos);
                break;

            case 8:
                if (salvarCarteira(carteira, qtdAtivos)) {
                    printf("\nDados salvos com sucesso em data/carteira.txt!\n");
                }
                sair();
                break;

            default:
                printf("\nOpcao invalida. Escolha uma opcao de 1 a 8.\n");
                break;
        }
    }

    return 0;
}
