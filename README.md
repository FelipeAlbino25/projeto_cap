# Jogo de Batalha Naval em C

## Descrição
Este projeto é uma implementação do clássico jogo Batalha Naval em linguagem C, onde o jogador enfrenta a máquina em um tabuleiro 8x8. O objetivo é afundar todos os navios do oponente antes que ele afunde os seus.

## Funcionalidades 
- Posicionamento manual dos navios pelo jogador
- Posicionamento aleatório dos navios do computador
- Sistema de turnos alternados (jogador vs computador)
- Registro de tentativas e acertos
- Visualização dos tabuleiros (seu campo, tentativas e campo inimigo)
- Verificação de vitória/derrota

## Como Jogar
1. Ao iniciar o jogo, posicione seus 4 navios seguindo as instruções:
    - Escolha orientação (vertical/horizontal)
    - Informe as coordenadas iniciais (linha e coluna)
2. No seu turno:
    - Informe as coordenadas para atacar (linha e coluna)
3. O computador jogará automaticamente após cada sua jogada
4. O jogo continua até que todos os navios de um dos jogadores sejam afundados


## Representação do Tabuleiro
- `~` - Água (posição vazia)
- `N` - Navio
- `0` - Tiro certeiro (acertou um navio)
- `X` - Tiro na água (errou)

## Requisitos
- Compilador C (gcc recomendado)
- Sistema operacional com terminal

## Instalação

1. Clone o projeto
```sh
   git clone https://github.com/FelipeAlbino25/projeto_cap.git
   ```
2. Compile o código
```sh
    gcc main.c -o batalha-naval
    ./batalha-naval
   ```

## Estrutura do Código
- `inicializar_campo()` - Preenche o tabuleiro com água
- `pode_posicionar()` - Verifica se um navio pode ser colocado em determinada posição 
- `posicionar_navio()` - Posiciona navios do computador aleatorioamente
- `posicionar_navio_jogador()` _ Posiciona navios do jogador
- `imprimir_campo()` - Exibe o tabuleiro atual
- `atirar_alvo()` - Processa ataque do jogador
- `turno_inimigo()` - Implementa a jogada do computador
- `campo_vazio()` - Verifica se ainda há navios no tabuleiro


