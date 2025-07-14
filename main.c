#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

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
        for (int i = 0; i < tamanho; i++) {
            if (campo[x][y + i] != '~') return 0;
            // Verifica células adjacentes
            if (x > 0 && campo[x-1][y+i] != '~') return 0; // acima
            if (x < TAM-1 && campo[x+1][y+i] != '~') return 0; // abaixo
        }
        // Verifica extremidades
        if (y > 0 && campo[x][y-1] != '~') return 0; // esquerda
        if (y + tamanho < TAM && campo[x][y+tamanho] != '~') return 0; // direita
    } else { // Vertical
        if (x + tamanho > TAM) return 0;
        for (int i = 0; i < tamanho; i++) {
            if (campo[x + i][y] != '~') return 0;
            // Verifica células adjacentes
            if (y > 0 && campo[x+i][y-1] != '~') return 0; // esquerda
            if (y < TAM-1 && campo[x+i][y+1] != '~') return 0; // direita
        }
        // Verifica extremidades
        if (x > 0 && campo[x-1][y] != '~') return 0; // acima
        if (x + tamanho < TAM && campo[x+tamanho][y] != '~') return 0; // abaixo
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
void imprimir_campo(char campo[TAM][TAM], char legenda[]) {
    printf("\n+----------------------------+\n");
    printf(" %-27s \n", legenda);
    printf("+---+------------------------+\n");
    printf("|   | 0  1  2  3  4  5  6  7 |\n");
    printf("+---+------------------------+\n");
    
    for (int i = 0; i < TAM; i++) {
        printf("| %d |", i);
        for (int j = 0; j < TAM; j++) {
            switch(campo[i][j]) {
                case '~': printf("\033[34m ~ \033[0m"); break;  // Água
                case 'N': printf("\033[33m N \033[0m"); break;  // Navio
                case 'O': printf("\033[31m X \033[0m"); break;  // Seu acerto
                case 'X': printf("\033[37m o \033[0m"); break;  // Seu erro (campo tentativas)
                case 'A': printf("\033[31m X \033[0m"); break;  // Acerto inimigo
                case 'E': printf("\033[37m o \033[0m"); break;  // Erro inimigo
                default: printf(" %c ", campo[i][j]);
            }
        }
        printf("|\n");
        if (i < TAM-1) printf("|   |                        |\n");
    }
    printf("+---+------------------------+\n");
}

void popular_campo_jogador(char campo[TAM][TAM]) {

    inicializar_campo(campo);

    char input[200];
    int orientacao, linha, coluna;

    printf("\n\nSEU CAMPO\n");
    imprimir_campo(campo,"Jogador");

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
        imprimir_campo(campo,"Jogador");
    }
}

void popular_campo_tentativa(char campo[TAM][TAM]){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            campo[i][j] = '~';
        }
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

void atirar_alvo(int linha, int coluna, char campoInimigo[TAM][TAM], char campoTentativa[TAM][TAM], int *counter) {
    if(linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM) {
        printf("\n\n>> Coordenadas inválidas! Use valores entre 0 e %d.\n", TAM-1);
        return;
    }

    if(campoTentativa[linha][coluna] == 'X' || campoTentativa[linha][coluna] == 'O') {
        printf("\n\n>> Você já tentou esta coordenada (%d,%d)! Tente outra.\n", linha, coluna);
        return;
    }

    if(campoInimigo[linha][coluna] == 'N') {
        *counter += 1;
        campoInimigo[linha][coluna] = '~';
        campoTentativa[linha][coluna] = 'O';
        
        // Feedback diferente baseado no tamanho do navio atingido
        int tamanho_navio = 0;
        for(int i = 0; i < NUM_NAVIOS; i++) {
            if(tamanhos_navios[i] <= *counter) {
                tamanho_navio = tamanhos_navios[i];
            }
        }
        
        printf("\n\n>> Você acertou um navio inimigo!");
        printf("\n>> Tamanho estimado do navio: %d", tamanho_navio);
        printf("\n>> Acertos totais: %d\n", *counter);
    } 
    else {
        campoTentativa[linha][coluna] = 'X';
        printf("\n\n>> Água! Seu tiro em (%d,%d) não acertou nada.\n", linha, coluna);
    }
}

bool campo_vazio(char campo[TAM][TAM]){
    for(int i=0; i<TAM;i++){
        for(int j=0; j<TAM;j++){
            if(campo[i][j]!='~'){
                return false;
            }
        }
    }
    return true;
}

bool verificar_tentativa(int casa, int campo[64]){

    for(int i=0;i<64;i++){
        if(campo[i]==casa) return true;
    }
    return false;
}

void turno_inimigo(char campo[TAM][TAM], int *counter) {
    static int ultimos_acertos[2][2] = {{-1,-1}, {-1,-1}};
    static int direcao[2] = {0,0}; // dx, dy
    static int modo = 0; // 0=aleatório, 1=perseguindo, 2=seguindo linha
    
    int linha, coluna;
    
    // Detecta padrão linear após 2 acertos
    if (modo == 1 && ultimos_acertos[1][0] != -1) {
        direcao[0] = ultimos_acertos[1][0] - ultimos_acertos[0][0];
        direcao[1] = ultimos_acertos[1][1] - ultimos_acertos[0][1];
        modo = 2;
    }

    if (modo == 2) { // Modo linha reta
        linha = ultimos_acertos[1][0] + direcao[0];
        coluna = ultimos_acertos[1][1] + direcao[1];
        
        if (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM || 
            campo[linha][coluna] == 'A' || campo[linha][coluna] == 'E') {
            modo = 0;
        }
    }

    if (modo == 0 || modo == 1) {
        do {
            if (modo == 1 && ultimos_acertos[0][0] != -1) {
                int tentativas[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
                int tentativa = rand() % 4;
                linha = ultimos_acertos[0][0] + tentativas[tentativa][0];
                coluna = ultimos_acertos[0][1] + tentativas[tentativa][1];
            } else {
                linha = rand() % TAM;
                coluna = rand() % TAM;
            }
        } while (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM || 
                campo[linha][coluna] == 'A' || campo[linha][coluna] == 'E');
    }

    // Executa o ataque
    if (campo[linha][coluna] == 'N') {
        *counter += 1;
        campo[linha][coluna] = 'A';
        printf("\n>> INIMIGO ACERTOU! (Acertos: %d)\n", *counter);

        // Atualiza histórico
        if (modo == 0 || modo == 1) {
            ultimos_acertos[1][0] = ultimos_acertos[0][0];
            ultimos_acertos[1][1] = ultimos_acertos[0][1];
            ultimos_acertos[0][0] = linha;
            ultimos_acertos[0][1] = coluna;
            modo = 1;
        } else {
            ultimos_acertos[1][0] = linha;
            ultimos_acertos[1][1] = coluna;
        }
    } else {
        campo[linha][coluna] = 'E';
        printf("\n>> Inimigo errou!\n");
        
        if (modo == 2) {
            modo = 0;
            ultimos_acertos[0][0] = -1;
            ultimos_acertos[0][1] = -1;
        }
    }
}


int main(void){
    srand(time(NULL));

    char campo_inimigo[TAM][TAM];
    popular_campo_inimigo(campo_inimigo);

    char campo_jogador[TAM][TAM];
    popular_campo_jogador(campo_jogador);

    char campo_tentativa[TAM][TAM];
    popular_campo_tentativa(campo_tentativa);

    char input[100];
    int linha;
    int coluna;
    int counter_acertos_jogador=0;
    int counter_acertos_inimigo=0;
    while(!campo_vazio(campo_inimigo) && !campo_vazio(campo_jogador)){

        printf(">>Insira uma coordenada para atacar (Linha, Coluna, Ex: 3 4)");
        fgets(input, sizeof input, stdin);
        sscanf(input, "%d%d",&linha, &coluna);
        turno_inimigo(campo_jogador,&counter_acertos_inimigo);
        imprimir_campo(campo_jogador,"Jogador");
        
        atirar_alvo(linha,coluna,campo_inimigo,campo_tentativa,&counter_acertos_jogador);
        imprimir_campo(campo_tentativa,"Tentativas");
    }

    if(campo_vazio(campo_inimigo)) printf("Voce ganhou!!! Parabens!");
    else printf("O Computador Ganhou!!! Desista dos seus sonhos!");
    
}