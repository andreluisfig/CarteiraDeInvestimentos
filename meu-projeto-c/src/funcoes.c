// Importação das bibliotecas padrão do C e do cabeçalho de funções do projeto
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "funcoes.h" 

// Função auxiliar para limpar o buffer do teclado e evitar falhas nas próximas leituras de dados
void limparBuffer(void) { 
    int c; 
    while ((c = getchar()) != '\n' && c != EOF) { 
        /* Descarta caracteres restantes no buffer de entrada */ 
    } 
} 

// Função que encerra o programa de forma segura caso a entrada de dados seja interrompida (EOF)
void encerrarPorFimDeEntrada(void) { 
    /* Os ativos ja cadastrados sao salvos a cada cadastro, entao nada se perde */ 
    printf("\nEntrada encerrada. Ate logo!\n"); 
    exit(0); 
} 

// Lê uma string informada pelo usuário de forma segura, prevenindo overflow e validando o conteúdo
void lerTexto(const char *rotulo, char destino[], int tamanho) { 
    char linha[256]; 
    size_t len; 

    while (1) { 
        printf("%s", rotulo); 
        // Lê a entrada do usuário e verifica se houve interrupção (EOF)
        if (fgets(linha, sizeof(linha), stdin) == NULL) { 
            encerrarPorFimDeEntrada(); 
        } 

        len = strlen(linha); 
        // Remove o caractere de quebra de linha ('\n') do final da string, se existir
        if (len > 0 && linha[len - 1] == '\n') { 
            linha[len - 1] = '\0'; 
        } else { 
            /* Linha maior que o buffer: descarta o restante */ 
            limparBuffer(); 
        } 

        // Validações básicas: impede strings vazias e o uso de ponto e vírgula
        if (linha[0] == '\0') { 
            printf("Erro: o campo nao pode ficar vazio.\n"); 
        } else if (strchr(linha, ';') != NULL) { 
            printf("Erro: nao use ponto e virgula (;) neste campo.\n"); 
        } else { 
            // Copia a string validada para a variável de destino respeitando o limite de tamanho
            strncpy(destino, linha, (size_t)tamanho - 1); 
            destino[tamanho - 1] = '\0'; 
            return; 
        } 
    } 
} 

// Lê e valida a quantidade do ativo, garantindo que seja um número inteiro positivo
int lerQuantidade(void) { 
    int quantidade; 
    int resultado; 

    while (1) { 
        printf("Quantidade: "); 
        resultado = scanf("%d", &quantidade); 
        // Verifica se a entrada foi encerrada abruptamente
        if (resultado == EOF) { 
            encerrarPorFimDeEntrada(); 
        } 
        // Se a leitura for bem sucedida e a quantidade for maior que zero, retorna o valor
        if (resultado == 1 && quantidade > 0) { 
            limparBuffer(); 
            return quantidade; 
        } 
        // Caso contrário, exibe erro e limpa o buffer para nova tentativa
        printf("Erro: a quantidade deve ser um inteiro maior que zero.\n"); 
        limparBuffer(); 
    } 
} 

// Lê e valida o preço de compra, garantindo que seja um número decimal (double) maior que zero
double lerPrecoCompra(void) { 
    double preco; 
    int resultado; 

    while (1) { 
        printf("Preco de compra (R$): "); 
        resultado = scanf("%lf", &preco); 
        if (resultado == EOF) { 
            encerrarPorFimDeEntrada(); 
        } 
        // O preço de compra deve ser estritamente maior que zero
        if (resultado == 1 && preco > 0.0) { 
            limparBuffer(); 
            return preco; 
        } 
        printf("Erro: o preco de compra deve ser maior que zero.\n"); 
        limparBuffer(); 
    } 
} 

// Lê e valida o preço atual do ativo, garantindo que não seja um valor negativo
double lerPrecoAtual(void) { 
    double preco; 
    int resultado; 

    while (1) { 
        printf("Preco atual (R$): "); 
        resultado = scanf("%lf", &preco); 
        if (resultado == EOF) { 
            encerrarPorFimDeEntrada(); 
        } 
        // O preço atual pode ser zero, mas não negativo
        if (resultado == 1 && preco >= 0.0) { 
            limparBuffer(); 
            return preco; 
        } 
        printf("Erro: o preco atual nao pode ser negativo.\n"); 
        limparBuffer(); 
    } 
} 

// Função principal de cadastro de um novo ativo na carteira
int cadastrarAtivo(Ativo carteira[], int qtdAtual) { 
    // Verifica se a carteira já atingiu a capacidade máxima antes de tentar cadastrar
    if (qtdAtual >= MAX_ATIVOS) { 
        printf("\nLimite maximo de ativos atingido (%d ativos)!\n", MAX_ATIVOS); 
        return qtdAtual; 
    } 

    printf("\n--- Cadastro de Ativo ---\n"); 

    /* Le o nome e a categoria aceitando espacos e recusando ponto e virgula */ 
    lerTexto("Nome (ex: PETR4, TESOURO SELIC): ", carteira[qtdAtual].nome, 
             (int)sizeof(carteira[qtdAtual].nome)); 
    lerTexto("Categoria (ex: Acao, Renda Fixa): ", carteira[qtdAtual].categoria, 
             (int)sizeof(carteira[qtdAtual].categoria)); 

    // Obtém os dados numéricos utilizando as funções de validação criadas acima
    carteira[qtdAtual].quantidade  = lerQuantidade(); 
    carteira[qtdAtual].precoCompra = lerPrecoCompra(); 
    carteira[qtdAtual].precoAtual  = lerPrecoAtual(); 

    printf("\nAtivo cadastrado com sucesso!\n"); 
    // Retorna a nova quantidade de ativos (incrementada em 1)
    return qtdAtual + 1; 
} 

// Calcula a rentabilidade percentual individual de um ativo
double calcularRentabilidade(double precoCompra, double precoAtual) { 
    if (precoCompra <= 0.0) { 
        return 0.0; 
    } 
    // Fórmula: ((Valor Atual - Valor de Compra) / Valor de Compra) * 100
    return ((precoAtual - precoCompra) / precoCompra) * 100.0; 
} 

// Calcula o valor monetário absoluto de lucro ou prejuízo do ativo
double calcularLucroPrejuizo(double precoCompra, double precoAtual, int quantidade) { 
    return (precoAtual - precoCompra) * quantidade; 
} 

// Itera sobre a carteira e calcula o valor total atual de todos os ativos somados
double calcularValorTotal(const Ativo carteira[], int qtdAtual) { 
    double total = 0.0; 
    int i; 

    for (i = 0; i < qtdAtual; i++) { 
        total += carteira[i].precoAtual * carteira[i].quantidade; 
    } 
    return total; 
} 

// Itera sobre a carteira e calcula o valor total gasto inicialmente para adquirir os ativos
double calcularTotalInvestido(const Ativo carteira[], int qtdAtual) { 
    double totalInvestido = 0.0; 
    int i; 

    for (i = 0; i < qtdAtual; i++) { 
        totalInvestido += carteira[i].precoCompra * carteira[i].quantidade; 
    } 
    return totalInvestido; 
} 

// Subtrai o total investido do total atual para descobrir o lucro/prejuízo global em reais
double calcularLucroPrejuizoTotal(const Ativo carteira[], int qtdAtual) { 
    return calcularValorTotal(carteira, qtdAtual) - calcularTotalInvestido(carteira, qtdAtual); 
} 

// Calcula a rentabilidade percentual geral considerando toda a carteira de investimentos
double calcularRentabilidadeGeral(const Ativo carteira[], int qtdAtual) { 
    double totalInvestido = calcularTotalInvestido(carteira, qtdAtual); 
    double valorTotalAtual = calcularValorTotal(carteira, qtdAtual); 

    // Evita divisão por zero caso o total investido seja nulo
    if (totalInvestido <= 0.0) { 
        return 0.0; 
    } 
    return ((valorTotalAtual - totalInvestido) / totalInvestido) * 100.0; 
} 

// Percorre e imprime na tela todos os ativos cadastrados, detalhando métricas financeiras
void listarCarteira(const Ativo carteira[], int qtdAtual) { 
    int i; 

    // Se não houver ativos, avisa o usuário e sai da função
    if (qtdAtual == 0) { 
        printf("\nNenhum ativo cadastrado na carteira.\n"); 
        return; 
    } 

    printf("\n=== ATIVOS DA CARTEIRA ===\n"); 
    for (i = 0; i < qtdAtual; i++) { 
        // Cálculos individuais prévios para formatação limpa da saída
        double valorInvestidoAtivo = carteira[i].precoCompra * carteira[i].quantidade; 
        double valorAtualAtivo = carteira[i].precoAtual * carteira[i].quantidade; 
        double lucroPrejuizo = calcularLucroPrejuizo( 
            carteira[i].precoCompra, 
            carteira[i].precoAtual, 
            carteira[i].quantidade 
        ); 
        double rentabilidadeAtivo = calcularRentabilidade( 
            carteira[i].precoCompra, 
            carteira[i].precoAtual 
        ); 

        // Impressão dos dados do ativo (Nome, Categoria, Qtd e Preços)
        printf("%d. %s (%s) - %d unid. | Compra: R$ %.2f | Atual: R$ %.2f\n", 
               i + 1, 
               carteira[i].nome, 
               carteira[i].categoria, 
               carteira[i].quantidade, 
               carteira[i].precoCompra, 
               carteira[i].precoAtual); 
        // Impressão dos resultados e percentuais (Investido, Atual e Lucro/Prejuízo)
        printf("   Investido: R$ %.2f | Valor atual: R$ %.2f | Resultado: %+0.2f (%.2f%%)\n\n", 
               valorInvestidoAtivo, 
               valorAtualAtivo, 
               lucroPrejuizo, 
               rentabilidadeAtivo); 
    } 

    // Rodapé da listagem com totais da carteira
    printf("Valor total da carteira: R$ %.2f\n", calcularValorTotal(carteira, qtdAtual)); 
    printf("Rentabilidade geral: %.2f%%\n", calcularRentabilidadeGeral(carteira, qtdAtual)); 
} 

// Exibe um resumo rápido focando apenas no dinheiro injetado versus dinheiro atual
void exibirValorTotal(const Ativo carteira[], int qtdAtual) { 
    if (qtdAtual == 0) { 
        printf("\nNenhum ativo cadastrado na carteira.\n"); 
        return; 
    } 

    printf("\n=== VALOR TOTAL DA CARTEIRA ===\n"); 
    printf("Total investido na compra: R$ %.2f\n", calcularTotalInvestido(carteira, qtdAtual)); 
    printf("Valor total atual:         R$ %.2f\n", calcularValorTotal(carteira, qtdAtual)); 
} 

// Exibe um resumo focado na métrica de rentabilidade geral (% e financeiro)
void exibirRentabilidadeGeral(const Ativo carteira[], int qtdAtual) { 
    double investido; 
    double atual; 
    double diferenca; 
    double rentabilidadeGeral; 

    if (qtdAtual == 0) { 
        printf("\nNenhum ativo cadastrado na carteira.\n"); 
        return; 
    } 

    // Obtém os dados consolidados utilizando as funções auxiliares
    investido = calcularTotalInvestido(carteira, qtdAtual); 
    atual = calcularValorTotal(carteira, qtdAtual); 
    diferenca = calcularLucroPrejuizoTotal(carteira, qtdAtual); 
    rentabilidadeGeral = calcularRentabilidadeGeral(carteira, qtdAtual); 

    printf("\n=== RENTABILIDADE GERAL DA CARTEIRA ===\n"); 
    printf("Valor total investido: R$ %.2f\n", investido); 
    printf("Valor total atual:     R$ %.2f\n", atual); 
    printf("Rentabilidade geral:   %.2f%%\n", rentabilidadeGeral); 

    // Formata a saída de acordo com o cenário: Lucro, Prejuízo ou Estável (Zero a Zero)
    if (diferenca > 0.0) { 
        printf("Lucro/Prejuizo total:  Lucro de R$ %.2f (+R$ %.2f)\n", diferenca, diferenca); 
    } else if (diferenca < 0.0) { 
        printf("Lucro/Prejuizo total:  Prejuizo de R$ %.2f (-R$ %.2f)\n", -diferenca, -diferenca); 
    } else { 
        printf("Lucro/Prejuizo total:  R$ 0.00 (estavel)\n"); 
    } 
} 

// Ordena o array de ativos (do mais rentável ao menos rentável) utilizando o algoritmo Bubble Sort
void ordenarPorRentabilidade(Ativo carteira[], int qtdAtual) { 
    int i, j; 
    int trocou; 

    // Retorna imediatamente se não houver necessidade de ordenação
    if (qtdAtual <= 1) { 
        return; 
    } 

    /* Algoritmo Bubble Sort: ordena da maior para a menor rentabilidade */ 
    for (i = 0; i < qtdAtual - 1; i++) { 
        trocou = 0; 
        for (j = 0; j < qtdAtual - 1 - i; j++) { 
            double rentAtual = calcularRentabilidade(carteira[j].precoCompra, carteira[j].precoAtual); 
            double rentProx  = calcularRentabilidade(carteira[j + 1].precoCompra, carteira[j + 1].precoAtual); 

            // Se a rentabilidade do ativo atual for menor que a do próximo, inverte a posição de ambos
            if (rentAtual < rentProx) { 
                Ativo temp = carteira[j]; 
                carteira[j] = carteira[j + 1]; 
                carteira[j + 1] = temp; 
                trocou = 1; 
            } 
        } 
        /* Se nenhuma troca ocorreu nesta passagem, o vetor ja esta ordenado */ 
        if (!trocou) { 
            break; 
        } 
    } 
} 

// Função que simula o rendimento da carteira baseando-se em cenários conservadores/típicos
void executarSimuladorEducativo(const Ativo carteira[], int qtdAtual) { 
    double valorBase = calcularValorTotal(carteira, qtdAtual); 
    double valorPoupanca; 
    double valorTesouro; 
    double valorCDB; 
    int mes; 

    // Se a carteira estiver vazia, utiliza um valor fictício padrão para que a simulação funcione
    if (qtdAtual == 0 || valorBase <= 0.0) { 
        printf("\nSua carteira ainda nao possui saldo cadastrado.\n"); 
        printf("Utilizando valor ilustrativo de R$ 50000.00 para fins educativos.\n"); 
        valorBase = 50000.0; 
    } 

    // Inicializa as simulações com o saldo de base
    valorPoupanca = valorBase; 
    valorTesouro  = valorBase; 
    valorCDB      = valorBase; 

    /* Aplica juros compostos ao longo de 12 meses usando as taxas em #define */ 
    // OBS: Espera-se que as constantes TAXA_POUPANCA, TAXA_TESOURO_SELIC, etc., estejam definidas em funcoes.h
    for (mes = 0; mes < MESES_SIMULACAO; mes++) { 
        valorPoupanca *= (1.0 + TAXA_POUPANCA); 
        valorTesouro  *= (1.0 + TAXA_TESOURO_SELIC); 
        valorCDB      *= (1.0 + TAXA_CDB_110_CDI); 
    } 

    // Impressão dos resultados projetados após os meses estipulados
    printf("\n=== SIMULADOR EDUCATIVO ===\n"); 
    printf("E se os R$ %.2f da sua carteira ficassem\n", valorBase); 
    printf("investidos por %d meses em cada opcao?\n\n", MESES_SIMULACAO); 

    printf("POUPANCA       (%.2f%%/mes):  R$ %.2f  (+R$ %.2f)\n", 
           TAXA_POUPANCA * 100.0, valorPoupanca, valorPoupanca - valorBase); 
    printf("TESOURO SELIC  (%.2f%%/mes):  R$ %.2f  (+R$ %.2f)\n", 
           TAXA_TESOURO_SELIC * 100.0, valorTesouro, valorTesouro - valorBase); 
    printf("CDB 110%% CDI   (%.2f%%/mes):  R$ %.2f  (+R$ %.2f)\n", 
           TAXA_CDB_110_CDI * 100.0, valorCDB, valorCDB - valorBase); 

    // Explicação educativa sobre o funcionamento e risco de cada um dos ativos simulados
    printf("\nO que isso significa?\n"); 
    printf("- Poupanca: rende menos, mas e o investimento mais conhecido.\n"); 
    printf("- Tesouro Selic: garantido pelo Tesouro Nacional, rende mais\n"); 
    printf("  que a poupanca e aceita aplicacoes a partir de ~R$ 150.\n"); 
    printf("- CDB: rende mais e e coberto pelo FGC ate R$ 250 mil;\n"); 
    printf("  verifique a liquidez, pois alguns travam o dinheiro por um prazo.\n"); 
    printf("\nE o risco? Quanto maior o rendimento prometido, mais atencao ele pede:\n"); 
    printf("poupanca e Tesouro Selic tem risco muito baixo; no CDB o risco depende do\n"); 
    printf("banco emissor (por isso o limite do FGC). Estas taxas sao ilustrativas:\n"); 
    printf("rendimentos passados nao garantem rendimentos futuros.\n"); 
} 

// Gera um painel completo consolidando todos os dados da carteira após a ordenação de performance
void exibirRelatorioFinal(Ativo carteira[], int qtdAtual) { 
    int i; 
    double totalInvestido; 
    double valorTotalAtual; 
    double rentabilidadeGeral; 
    double lucroPrejuizoTotal; 

    // Verifica se é possível gerar o relatório
    if (qtdAtual == 0) { 
        printf("\nNenhum ativo cadastrado para gerar o relatorio final.\n"); 
        return; 
    } 

    /* Garante que os ativos estejam ordenados do melhor para o pior desempenho */ 
    ordenarPorRentabilidade(carteira, qtdAtual); 

    // Coleta as métricas gerais utilizando as funções auxiliares
    totalInvestido     = calcularTotalInvestido(carteira, qtdAtual); 
    valorTotalAtual    = calcularValorTotal(carteira, qtdAtual); 
    rentabilidadeGeral = calcularRentabilidadeGeral(carteira, qtdAtual); 
    lucroPrejuizoTotal = calcularLucroPrejuizoTotal(carteira, qtdAtual); 

    // Imprime o cabeçalho do relatório
    printf("\n============================================================\n"); 
    printf("         RELATORIO FINAL DA CARTEIRA DE INVESTIMENTOS       \n"); 
    printf("============================================================\n"); 
    printf("\nRANKING DE ATIVOS (MELHOR PARA PIOR RENTABILIDADE): \n"); 
    
    // Tabela formatada contendo os ativos já ordenados
    printf("+----+----------------+--------------+------+---------------+---------------+------------+---------------+\n"); 
    printf("| #  | Ativo          | Categoria    | Qtd. | Investido (R$)| Atual (R$)    | Rentab.    | Resultado (R$)|\n"); 
    printf("+----+----------------+--------------+------+---------------+---------------+------------+---------------+\n"); 

    for (i = 0; i < qtdAtual; i++) { 
        double valorInvestido = carteira[i].precoCompra * carteira[i].quantidade; 
        double valorAtivo = carteira[i].precoAtual * carteira[i].quantidade; 
        double rentAtivo  = calcularRentabilidade(carteira[i].precoCompra, carteira[i].precoAtual); 
        double lucroAtivo = calcularLucroPrejuizo(carteira[i].precoCompra, carteira[i].precoAtual, carteira[i].quantidade); 

        // Exibe cada linha da tabela formatada
        printf("| %-2d | %-14.14s | %-12.12s | %4d | %13.2f | %13.2f | %9.2f%% | %13.2f |\n", 
               i + 1, carteira[i].nome, carteira[i].categoria, carteira[i].quantidade, 
               valorInvestido, valorAtivo, rentAtivo, lucroAtivo); 
        printf("+----+----------------+--------------+------+---------------+---------------+------------+---------------+\n"); 
    } 

    // Exibe o consolidado financeiro final
    printf("\n2. CONSOLIDADO FINANCEIRO DA CARTEIRA:\n"); 
    printf("   - Valor Total Investido:  R$ %.2f\n", totalInvestido); 
    printf("   - Valor Total Atual:      R$ %.2f\n", valorTotalAtual); 
    printf("   - Rentabilidade Geral:    %+.2f%%\n", rentabilidadeGeral); 
    
    if (lucroPrejuizoTotal >= 0.0) { 
        printf("   - Lucro/Prejuizo Total:   Lucro de R$ %.2f (+R$ %.2f)\n", 
               lucroPrejuizoTotal, lucroPrejuizoTotal); 
    } else { 
        printf("   - Lucro/Prejuizo Total:   Prejuizo de R$ %.2f (-R$ %.2f)\n", 
               -lucroPrejuizoTotal, -lucroPrejuizoTotal); 
    } 

    // Imprime nota descritiva sobre os Objetivos de Desenvolvimento Sustentável da ONU
    printf("\n3. IMPACTO SOCIAL E INCLUSAO FINANCEIRA (ODS 8.10 DA ONU):\n"); 
    printf("   Este sistema e seu simulador educativo apoiam diretamente a meta 8.10\n"); 
    printf("   dos Objetivos de Desenvolvimento Sustentavel da ONU, que visa fortalecer\n"); 
    printf("   a capacidade das instituicoes financeiras nacionais e ampliar o acesso\n"); 
    printf("   a servicos financeiros para todos. Ao traduzir conceitos como juros\n"); 
    printf("   compostos, liquidez, risco e rentabilidade (Poupanca, Tesouro Selic e CDB)\n"); 
    printf("   em uma linguagem simples e livre de jargoes bancarios, a ferramenta\n"); 
    printf("   democratiza a educacao financeira e empodera cidadaos iniciantes a\n"); 
    printf("   tomarem decisoes conscientes para proteger e multiplicar seu patrimonio.\n"); 
    printf("============================================================\n"); 
} 

// Função disparada no encerramento final da aplicação
void sair(void) { 
    printf("\nObrigado por utilizar a Carteira de Investimentos! Ate logo.\n"); 
}