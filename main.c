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
void imprimir_campo(char campo[TAM][TAM], char legenda[]) {
    printf("\n%s\n",legenda);
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

void atirar_alvo(int linha, int coluna, char campoInimigo[TAM][TAM],char campoTentativa[TAM][TAM], int *counter){

    if(campoInimigo[linha][coluna]=='N'){
        *counter+=1;
        campoInimigo[linha][coluna] = '~';
        printf("\n\n>>Acertou!\n(Acertos: %d)",*counter);
        campoTentativa[linha][coluna] = 'O';
        
    }
    else if(campoTentativa[linha][coluna]=='X' || campoTentativa[linha][coluna] == 'O'){
        printf("\n\n>>Voce ja tentou esta coordenada!");
    }
    else {
        campoTentativa[linha][coluna] = 'X';
        printf("\n\n>>Errou!\n");
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

void turno_inimigo(char campo[TAM][TAM], int *counter){
    srand(time(NULL));
    int coordenadas_tentadas[64] = {0}; 
    int tentativas = 0; 
    do {
        int linha = rand() % 8;
        int coluna = rand() % 8;
        int casa = 8 * linha + coluna;

        if (!verificar_tentativa(casa, coordenadas_tentadas)) {
            coordenadas_tentadas[tentativas++] = casa; 
            if (campo[linha][coluna] == 'N') {
                *counter +=1;
                campo[linha][coluna] = 'X';
                printf("\n\n>> Inimigo acertou! (Acertos: %d)\n",*counter);
                
                break;
            } else {
                printf("\n\n>> Inimigo errou!\n");
                break;
            }
        }
    } while (true);
    
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