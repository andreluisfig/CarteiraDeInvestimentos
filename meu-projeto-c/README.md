# Simulador de Carteira de Investimentos Acessíveis

## Descrição do Projeto
O **Simulador de Carteira de Investimentos** é uma ferramenta intuitiva em linguagem C voltada à **inclusão financeira (ODS 8.10 da ONU)**. O projeto busca reduzir a barreira de entrada no mercado financeiro causada por aplicativos bancários poluídos e termos técnicos complexos, permitindo que qualquer pessoa simule, organize e acompanhe múltiplos ativos financeiros com segurança e clareza.

## Público-Alvo
* Jovens em início de carreira e estudantes;
* Trabalhadores de baixa e média renda que desejam construir uma reserva financeira;
* Investidores iniciantes que buscam compreender, na prática e sem risco financeiro real, como funciona a diversificação e a rentabilidade de uma carteira.

## Funcionalidades
1. **Cadastrar Ativo**: Permite registrar múltiplos investimentos informando nome, categoria (ex.: Ação, Renda Fixa), quantidade, preço de compra e preço atual, com validação de dados.
2. **Listar Carteira**: Exibe todos os ativos cadastrados de forma limpa e organizada, apresentando o valor atual e a rentabilidade individual de cada ativo, além do resumo geral.
3. **Calcular Valor Total**: Soma automaticamente o patrimônio atual acumulado em todos os ativos da carteira e compara com o valor total investido.
4. **Calcular Rentabilidade Geral**: Compara o montante total gasto na compra com o valor atual de todos os investimentos juntos, entregando a porcentagem exata de ganho ou perda e o resultado em reais.
5. **Persistência Automática (`carteira.txt`)**: Carrega os ativos automaticamente ao iniciar o sistema e salva todas as alterações em arquivo texto (`data/carteira.txt`) entre execuções.

## Tecnologias Utilizadas
* **Linguagem**: C (padrão ANSI C / C99)
* **Ambiente de desenvolvimento**: MinGW-w64
* **Compilador**: GCC (GNU Compiler Collection)
* **Bibliotecas Padrão**: `<stdio.h>`

## Requisitos Mínimos
* Sistema Operacional Windows, Linux ou macOS;
* Compilador `gcc` instalado e configurado no terminal;
* Terminal de linha de comando para execução.

## Estrutura de Pastas
```text
meu-projeto-c/
├── src/
│   ├── main.c
│   ├── funcoes.c
│   └── modulo.c
├── include/
│   ├── funcoes.h
│   └── modulo.h
├── data/
│   └── carteira.txt
└── README.md

## Compilação
gcc -Wall -Wextra -Iinclude src/main.c src/funcoes.c src/modulo.c -o programa

## Execução
programa.exe

## Restrições atendidas
Sem ordenação