/*
    Trabalho final de Construção De Algoritmos e Programação - UFSCAR

    João Vitor da Silveira Silva 843018
    Felipe Congio Albino - 845143
    Luiz Henrique Simões Silva - 845576
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define TAM 8
#define NUM_NAVIOS 4
#define HORIZONTAL 2
#define VERTICAL 1

int tamanhos_navios[NUM_NAVIOS] = {4, 3, 2, 1};

/*
    Descrição: Função para colocar "água" no campo de navios
    Requer: Uma matriz quadrada de caracteres com dimensões TAM x TAM que será inicializada
    Assegura: Cada elemento campo[i][j] é atribuído com o valor '~', representando água 
*/
void inicializar_campo(char campo[TAM][TAM]);

/*
    Descrição: Verifica se é possível posicionar um navio de determinado tamanho em uma posição específica do tabuleiro, impedindo  colisões
    Requer: A matriz campo, coordenada da linha, da coluna, o tamanho do navio a ser posicionado e a orientação dele (vertical ou horizontal)
    Assegura: Retorna 1 (true) se o navio pode ser posicionado na posição especificada e 0 (false) se o navio ultrapassa os limites do tabuleiro ou se ja existe outro navio no lugar.

*/
int pode_posicionar(char campo[TAM][TAM], int x, int y, int tamanho, int orientacao);

/*
    Descrição: Posiciona um navio de determinado tamanho em um campo de batalha de forma aleatória.
    Requer: A matriz campo, que representa o tabuleiro, e o tamanho do navio a ser posicionado.
    Assegura: Que o navio seja posicionado em uma posição válida com 'N'.
*/
void posicionar_navio(char campo[TAM][TAM], int tamanho);

/*
    Descrição: Inicializa e preenche um tabuleiro de jogo com navios posicionados aleatoriamente, representando o campo do oponente/computador.
    Requer: A matriz campo[TAM][TAM].
    Assegura: Que os navios do campo do oponente sejam posicionados.
*/
void popular_campo_inimigo(char campo[TAM][TAM]);

/*
    Descrição: Exibe visualmente o tabuleiro do jogo no console, com formatação colorida e legenda.
    Requer: A matriz campo[TAM][TAM] e a legenda a ser exibida acima do tabuleiro.
    Assegura: Que o tabuleiro seja imprimido no console.
*/
void imprimir_campo(char campo[TAM][TAM], char legenda[]);

/*
    Descrição: Permite que o jogador posicione manualmente seus navios no tabuleiro.
    Requer: A matriz campo[TAM][TAM] e as funções inicializar_campo(), imprimir_campo(), pode_posicionar() e posicionar_navio_jogador().
    Assegura: Que o jogador posicione seus navios.
*/
void popular_campo_jogador(char campo[TAM][TAM]);

/*
    Descrição: Inicializa um tabuleiro secundário, que represanta as tentativas do jogador.
    Requer: A matriz campo[TAM][TAM].
    Assegura: Que o tabuleiro seja inicializado corretamente.
*/
void popular_campo_tentativa(char campo[TAM][TAM]);

/*
    Descrição: Insere um navio no tabuleiro do jogador na posição e orientação especificadas, marcando as posições ocupadas com o caractere 'N'.
    Requer: A matriz campo[TAM][TAM], coordenada y (linha), coordenada x (coluna), o tamanho de casas que o navio ocupa e a orientação (horizontal ou vertical).
    Assegura: Que o jogador consiga posicionar seus navios corretamente.
*/
void posicionar_navio_jogador(char campo[TAM][TAM], int linha, int coluna, int tamanho, int orientacao);

/*
    Descrição: Processa um disparo do jogador contra o campo inimigo, verificando se o tiro acertou um navio ou não, atualizando os tabuleiros e fornecendo feedback ao jogador.
    Requer: Coordenada y (linha), coordenada x (coluna), a matriz campo_inimigo, a matriz campo_tentativa e um ponteiro para contar os acertos.
    Assegura: Que as coordenadas estejam dentro do tabuleiro, se ja foram tentadas anteriormente e exibe se jogador acertou ou errou o navio inimigo.
*/
void atirar_alvo(int linha, int coluna, char campo_inimigo[TAM][TAM], char campo_tentativa[TAM][TAM], int *contador);

/*
    Descrição: Verifica se um tabuleiro de jogo está completamente vazio, ou seja, contém apenas o caractere '~'.
    Requer: A matriz campo[TAM][TAM].
    Assegura: Se encontrar algum valor diferente de "~" retorna false, se completar a varredura completa retorna true.
*/
bool campo_vazio(char campo[TAM][TAM]);

/*
    Descrição: Verifica se um determinado valor (representando uma posição/jogada) já existe em um vetor que armazena tentativas anteriores.
    Requer: A matriz campo[TAM][TAM] e um vetor contendo as tentativas/jogadas anteriores.
    Assegura: Retorna true se o valor já existe no vetor, false caso contrário.
*/
bool verificar_tentativa(int casa, int campo[64]);

/*
    Descrição: Implementa a lógica de ataque do oponente computacional, com três estratégias diferentes de ataque que evoluem conforme o desempenho do inimigo, com detecção de padrões. Modo linha reta (continua na direção estabelecida), modo perseguição (testa posições adjacentes ao último acerto) e modo aleatório (escolhe posições aleatórias).
    Requer: A matriz campo[TAM][TAM] e um vetor que conta os acertos do inimigo.
    Assegura: Verifica se coordenadas estão dentro do tabuleiro e confirma que posição não foi tentada anteriormente.
*/
void turno_inimigo(char campo[TAM][TAM], int *contador);

int main(void)
{
    srand(time(NULL));

    char campo_inimigo[TAM][TAM];
    popular_campo_inimigo(campo_inimigo);

    char campo_jogador[TAM][TAM];
    popular_campo_jogador(campo_jogador);

    char campo_tentativa[TAM][TAM];
    popular_campo_tentativa(campo_tentativa);

    char input[100];
    int linha, coluna;
    int contador_acertos_jogador = 0;
    int contador_acertos_inimigo = 0;
    while (!campo_vazio(campo_inimigo) && !campo_vazio(campo_jogador))
    {

        printf(">> Insira uma coordenada para atacar (Linha, Coluna, Ex: 3 4)");
        fgets(input, sizeof input, stdin);
        sscanf(input, "%d%d", &linha, &coluna);
        turno_inimigo(campo_jogador, &contador_acertos_inimigo);
        imprimir_campo(campo_jogador, "Jogador");

        atirar_alvo(linha, coluna, campo_inimigo, campo_tentativa, &contador_acertos_jogador);
        imprimir_campo(campo_tentativa, "Tentativas");
    }

    if (campo_vazio(campo_inimigo))
        printf("Voce ganhou!!! Parabens!");
    else
        printf("O Computador Ganhou!!! Desista dos seus sonhos!");
}

void inicializar_campo(char campo[TAM][TAM])
{
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            campo[i][j] = '~'; // água
}

int pode_posicionar(char campo[TAM][TAM], int x, int y, int tamanho, int orientacao)
{

    if (orientacao == HORIZONTAL)
    { 
        if (y + tamanho > TAM)
            return 0;

        for (int i = 0; i < tamanho; i++)

            if (campo[x][y + i] != '~')
                return 0;
    }
    else
    { // Vertical

        if (x + tamanho > TAM)
            return 0;

        for (int i = 0; i < tamanho; i++)

            if (campo[x + i][y] != '~')
                return 0;
    }

    return 1;
}

void posicionar_navio(char campo[TAM][TAM], int tamanho)
{
    int x, y, orientacao;
    do
    {
        x = rand() % TAM;
        y = rand() % TAM;
        orientacao = rand() % 2; // 0 = horizontal, 1 = vertical
    } while (!pode_posicionar(campo, x, y, tamanho, orientacao));

    if (orientacao == 0)
        for (int i = 0; i < tamanho; i++)
            campo[x][y + i] = 'N';
    else
        for (int i = 0; i < tamanho; i++)
            campo[x + i][y] = 'N';
}

void popular_campo_inimigo(char campo[TAM][TAM])
{
    inicializar_campo(campo);
    for (int i = 0; i < NUM_NAVIOS; i++)
    {
        posicionar_navio(campo, tamanhos_navios[i]);
    }
}

void imprimir_campo(char campo[TAM][TAM], char legenda[])
{
    printf("\n+----------------------------+\n");
    printf(" %-27s \n", legenda);
    printf("+---+------------------------+\n");
    printf("|   | 0  1  2  3  4  5  6  7 |\n");
    printf("+---+------------------------+\n");

    for (int i = 0; i < TAM; i++)
    {
        printf("| %d |", i);
        for (int j = 0; j < TAM; j++)
        {
            switch (campo[i][j])
            {
            case '~':
                printf("\033[34m ~ \033[0m");
                break; // Água
            case 'N':
                printf("\033[33m N \033[0m");
                break; // Navio
            case 'O':
                printf("\033[31m X \033[0m");
                break; // Seu acerto
            case 'X':
                printf("\033[37m o \033[0m");
                break; // Seu erro (campo tentativas)
            case 'A':
                printf("\033[31m X \033[0m");
                break; // Acerto inimigo
            case 'E':
                printf("\033[37m o \033[0m");
                break; // Erro inimigo
            default:
                printf(" %c ", campo[i][j]);
            }
        }
        printf("|\n");
        if (i < TAM - 1)
            printf("|   |                        |\n");
    }
    printf("+---+------------------------+\n");
}

void popular_campo_jogador(char campo[TAM][TAM])
{

    inicializar_campo(campo);

    char input[200];
    int orientacao, linha, coluna;

    printf("\n\nSEU CAMPO");
    imprimir_campo(campo, "Jogador");

    for (int i = 0; i < 4; i++)
    {

        int tamanho = tamanhos_navios[i];
        printf(">> Navio %d (Tamanho: %d)\n", i + 1, tamanho);

        do
        {
            printf(">> Insira a orientação (1-Vertical, 2-Horizontal): ");
            fgets(input, sizeof input, stdin);
            sscanf(input, "%d", &orientacao);
        } while (orientacao != 1 && orientacao != 2);

        do
        {
            printf(">> Insira a posição da Linha e da Coluna (ex: 3 4): ");
            fgets(input, sizeof input, stdin);
            sscanf(input, "%d %d", &linha, &coluna);
        } while (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM ||
                 !pode_posicionar(campo, linha, coluna, tamanho, orientacao));

        posicionar_navio_jogador(campo, linha, coluna, tamanho, orientacao);
        printf("\n\nSEU CAMPO");
        imprimir_campo(campo, "Jogador");
    }
}

void popular_campo_tentativa(char campo[TAM][TAM])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            campo[i][j] = '~';
        }
    }
}

void posicionar_navio_jogador(char campo[TAM][TAM], int linha, int coluna, int tamanho, int orientacao)
{
    if (orientacao == HORIZONTAL)
    { 
        for (int i = 0; i < tamanho; i++)
            campo[linha][coluna + i] = 'N';
    }
    else
    {
        for (int i = 0; i < tamanho; i++)
            campo[linha + i][coluna] = 'N';
    }
}

void atirar_alvo(int linha, int coluna, char campo_inimigo[TAM][TAM], char campo_tentativa[TAM][TAM], int *contador)
{
    if (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM)
    {
        printf("\n\n>> Coordenadas inválidas! Use valores entre 0 e %d.\n", TAM - 1);
        return;
    }

    if (campo_tentativa[linha][coluna] == 'X' || campo_tentativa[linha][coluna] == 'O')
    {
        printf("\n\n>> Você já tentou esta coordenada (%d,%d)! Tente outra.\n", linha, coluna);
        return;
    }

    if (campo_inimigo[linha][coluna] == 'N')
    {
        *contador += 1;
        campo_inimigo[linha][coluna] = '~';
        campo_tentativa[linha][coluna] = 'O';

        // Feedback diferente baseado no tamanho do navio atingido
        int tamanho_navio = 0;
        for (int i = 0; i < NUM_NAVIOS; i++)
        {
            if (tamanhos_navios[i] <= *contador)
            {
                tamanho_navio = tamanhos_navios[i];
            }
        }

        printf("\n\n>> Você acertou um navio inimigo!");
        printf("\n>> Tamanho estimado do navio: %d", tamanho_navio);
        printf("\n>> Acertos totais: %d\n", *contador);
    }
    else
    {
        campo_tentativa[linha][coluna] = 'X';
        printf("\n\n>> Água! Seu tiro em (%d,%d) não acertou nada.\n", linha, coluna);
    }
}

bool campo_vazio(char campo[TAM][TAM])
{
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            if (campo[i][j] != '~')
            {
                return false;
            }
        }
    }
    return true;
}

bool verificar_tentativa(int casa, int campo[64])
{
    for (int i = 0; i < 64; i++)
    {
        if (campo[i] == casa)
            return true;
    }
    return false;
}

void turno_inimigo(char campo[TAM][TAM], int *contador)
{
    static int ultimos_acertos[2][2] = {{-1, -1}, {-1, -1}};
    static int direcao[2] = {0, 0}; // dx, dy
    static int modo = 0;            // 0=aleatório, 1=perseguindo, 2=seguindo linha

    int linha, coluna;

    // Detecta padrão linear após 2 acertos
    if (modo == 1 && ultimos_acertos[1][0] != -1)
    {
        direcao[0] = ultimos_acertos[1][0] - ultimos_acertos[0][0];
        direcao[1] = ultimos_acertos[1][1] - ultimos_acertos[0][1];
        modo = 2;
    }

    if (modo == 2)
    { // Modo linha reta
        linha = ultimos_acertos[1][0] + direcao[0];
        coluna = ultimos_acertos[1][1] + direcao[1];

        if (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM ||
            campo[linha][coluna] == 'A' || campo[linha][coluna] == 'E')
        {
            modo = 0;   
        }
    }

    if (modo == 0 || modo == 1)
    {
        do
        {
            if (modo == 1 && ultimos_acertos[0][0] != -1)
            {
                int tentativas[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
                int tentativa = rand() % 4;
                linha = ultimos_acertos[0][0] + tentativas[tentativa][0];
                coluna = ultimos_acertos[0][1] + tentativas[tentativa][1];
            }
            else
            {
                linha = rand() % TAM;
                coluna = rand() % TAM;
            }
        } while (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM ||
                 campo[linha][coluna] == 'A' || campo[linha][coluna] == 'E');
    }

    // Executa o ataque
    if (campo[linha][coluna] == 'N')
    {
        *contador += 1;
        campo[linha][coluna] = 'A';
        printf("\n>> INIMIGO ACERTOU! (Acertos: %d)\n", *contador);

        // Atualiza histórico
        if (modo == 0 || modo == 1)
        {
            ultimos_acertos[1][0] = ultimos_acertos[0][0];
            ultimos_acertos[1][1] = ultimos_acertos[0][1];
            ultimos_acertos[0][0] = linha;
            ultimos_acertos[0][1] = coluna;
            modo = 1;
        }
        else
        {
            ultimos_acertos[1][0] = linha;
            ultimos_acertos[1][1] = coluna;
        }
    }
    else
    {
        campo[linha][coluna] = 'E';
        printf("\n>> Inimigo errou!\n");

        if (modo == 2)
        {
            modo = 0;
            ultimos_acertos[0][0] = -1;
            ultimos_acertos[0][1] = -1;
        }
    }
}