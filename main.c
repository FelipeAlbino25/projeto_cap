#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 8
#define NUM_NAVIOS 4

int tamanhos_navios[NUM_NAVIOS] = {4, 3, 2, 1};

/*
função para colocar água em um campo de navios
*/
void inicializar_campo(char campo[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            campo[i][j] = '~'; // água
}


/*
função que verifica se eu posso posicionar um navio em uma posição
*/
int pode_posicionar(char campo[TAM][TAM], int x, int y, int tamanho, int orientacao) {
    if (orientacao == 2) { // Horizontal
        if (y + tamanho > TAM) return 0;
        for (int i = 0; i < tamanho; i++)
            if (campo[x][y + i] != '~') return 0;
    } else { // Vertical
        if (x + tamanho > TAM) return 0;
        for (int i = 0; i < tamanho; i++)
            if (campo[x + i][y] != '~') return 0;
    }
    return 1;
}

/*
função para posicionar 1 navio
*/
void posicionar_navio(char campo[TAM][TAM], int tamanho) {
    int x, y, orientacao;
    do {
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
/*
popula o campo do inimigo que irá jogar contra o jogador
*/
void popular_campo_inimigo(char campo[TAM][TAM]) {
    inicializar_campo(campo);
    for (int i = 0; i < NUM_NAVIOS; i++) {
        posicionar_navio(campo, tamanhos_navios[i]);
    }
}
/*
imprime um campo qualquer
*/
void imprimir_campo(char campo[TAM][TAM]) {
    printf("  ");
    for (int i = 0; i < TAM; i++) printf("%d ", i);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAM; j++) {
            printf("%c ", campo[i][j]);
        }
        printf("\n");
    }
}

void popular_campo_jogador(char campo[TAM][TAM]) {

    inicializar_campo(campo);

    char input[200];
    int orientacao, linha, coluna;

    printf("\n\nSEU CAMPO\n");
    imprimir_campo(campo);

    for (int i = 0; i < 4; i++ ) {

        int tamanho = tamanhos_navios[i];
        printf(">> Navio %d (Tamanho: %d)\n", i + 1, tamanho);

        do {
            printf(">> Insira a orientação (1-Vertical, 2-Horizontal): ");
            fgets(input, sizeof input, stdin);
            sscanf(input, "%d", &orientacao);
        } while (orientacao != 1 && orientacao != 2);

        do {
            printf(">> Insira a posição da Coluna e da Linha (ex: 3 4): ");
            fgets(input, sizeof input, stdin);
            sscanf(input, "%d %d", &coluna, &linha);
        } while (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM || 
                 !pode_posicionar(campo, linha, coluna, tamanho, orientacao));

        posicionar_navio_jogador(campo, linha, coluna, tamanho, orientacao);
        printf("\n\nSEU CAMPO\n");
        imprimir_campo(campo);
    }
}

void posicionar_navio_jogador(char campo[TAM][TAM], int linha, int coluna, int tamanho, int orientacao) {
    if (orientacao == 2) { // Horizontal
        for (int i = 0; i < tamanho; i++)
            campo[linha][coluna + i] = 'N';
    } else { // Vertical
        for (int i = 0; i < tamanho; i++)
            campo[linha + i][coluna] = 'N';
    }
}


int main(void){
    srand(time(NULL));

    char campo_inimigo[TAM][TAM];
    popular_campo_inimigo(campo_inimigo);
    imprimir_campo(campo_inimigo);

    char campo_jogador[TAM][TAM];
    popular_campo_jogador(campo_jogador);
    imprimir_campo(campo_jogador);

    while(1){

    }
    
}