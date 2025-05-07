
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 10

// Funções utilitárias
void inicializar_tabuleiro(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = '~';
}

void exibir_tabuleiro(char tabuleiro[TAM][TAM]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("[%c]", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Posicionamento simples (Novato)
void posicionar_navio_vetor(char vetor[], int posicao, int tamanho) {
    for (int i = posicao; i < posicao + tamanho && i < TAM; i++) {
        vetor[i] = 'N';
    }
}

// Posicionamento em matriz (Aventureiro)
void posicionar_navio_matriz(char tabuleiro[TAM][TAM], int x, int y, int tamanho, char direcao) {
    for (int i = 0; i < tamanho; i++) {
        if (direcao == 'H' && y + i < TAM) {
            tabuleiro[x][y + i] = 'N';
        } else if (direcao == 'V' && x + i < TAM) {
            tabuleiro[x + i][y] = 'N';
        } else if (direcao == 'D' && x + i < TAM && y + i < TAM) {
            tabuleiro[x + i][y + i] = 'N';
        }
    }
}

// Habilidades especiais (Mestre)
void habilidade_cruz(char tabuleiro[TAM][TAM], int x, int y) {
    if (x >= 0 && x < TAM && y >= 0 && y < TAM) tabuleiro[x][y] = '*';
    if (x-1 >= 0) tabuleiro[x-1][y] = '*';
    if (x+1 < TAM) tabuleiro[x+1][y] = '*';
    if (y-1 >= 0) tabuleiro[x][y-1] = '*';
    if (y+1 < TAM) tabuleiro[x][y+1] = '*';
}

void habilidade_cone(char tabuleiro[TAM][TAM], int x, int y) {
    for (int i = x; i < x + 3 && i < TAM; i++) {
        for (int j = y - (i - x); j <= y + (i - x); j++) {
            if (j >= 0 && j < TAM) {
                tabuleiro[i][j] = '*';
            }
        }
    }
}

void habilidade_octaedro(char tabuleiro[TAM][TAM], int x, int y) {
    int alcance = 2;
    for (int i = -alcance; i <= alcance; i++) {
        for (int j = -alcance; j <= alcance; j++) {
            if (abs(i) + abs(j) <= alcance) {
                int xi = x + i;
                int yj = y + j;
                if (xi >= 0 && xi < TAM && yj >= 0 && yj < TAM) {
                    tabuleiro[xi][yj] = '*';
                }
            }
        }
    }
}

// Menu principal
int main() {
    char tabuleiro[TAM][TAM];
    char vetor[TAM];
    int opcao;

    do {
        printf("\n==== BATALHA NAVAL - MENU ====");
        printf("\n1. Módulo Novato (vetor)");
        printf("\n2. Módulo Aventureiro (matriz)");
        printf("\n3. Módulo Mestre (habilidades)");
        printf("\n0. Sair");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                printf("\n-- Módulo Novato --\n");
                memset(vetor, '~', sizeof(vetor));
                posicionar_navio_vetor(vetor, 3, 4);
                printf("Tabuleiro (vetor):\n");
                for (int i = 0; i < TAM; i++) {
                    printf("[%c]", vetor[i]);
                }
                printf("\n");
                break;
            }
            case 2: {
                printf("\n-- Módulo Aventureiro --\n");
                inicializar_tabuleiro(tabuleiro);
                posicionar_navio_matriz(tabuleiro, 2, 2, 3, 'H');
                posicionar_navio_matriz(tabuleiro, 4, 4, 3, 'D');
                exibir_tabuleiro(tabuleiro);
                break;
            }
            case 3: {
                printf("\n-- Módulo Mestre --\n");
                inicializar_tabuleiro(tabuleiro);
                habilidade_cruz(tabuleiro, 5, 5);
                habilidade_cone(tabuleiro, 1, 1);
                habilidade_octaedro(tabuleiro, 8, 8);
                exibir_tabuleiro(tabuleiro);
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
