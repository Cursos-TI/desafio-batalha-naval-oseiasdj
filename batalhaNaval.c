#include <stdio.h>

#define TAM 10      // Tamanho do tabuleiro
#define NAVIO 3     // Valor do navio no tabuleiro
#define HABIL 5     // Valor da área afetada pela habilidade
#define TAM_HAB 5   // Tamanho das matrizes de habilidade (5x5)

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;
}

// Função para posicionar navios fixos
void posicionarNavios(int tabuleiro[TAM][TAM]) {
    // Horizontal
    for (int i = 0; i < 3; i++) tabuleiro[1][1 + i] = NAVIO;
    // Vertical
    for (int i = 0; i < 3; i++) tabuleiro[4 + i][6] = NAVIO;
    // Diagonal principal
    for (int i = 0; i < 3; i++) tabuleiro[6 + i][6 + i] = NAVIO;
    // Diagonal secundária
    for (int i = 0; i < 3; i++) tabuleiro[i][9 - i] = NAVIO;
}

// Função para construir uma matriz de habilidade CONE
void construirCone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= (TAM_HAB - 1) / 2 - i && j <= (TAM_HAB - 1) / 2 + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função para construir uma matriz de habilidade CRUZ
void construirCruz(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função para construir uma matriz de habilidade OCTAEDRO (losango)
void construirOctaedro(int matriz[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função para aplicar matriz de habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM][TAM], int matriz[TAM_HAB][TAM_HAB], int origemLinha, int origemColuna) {
    int offset = TAM_HAB / 2;

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int lin = origemLinha - offset + i;
            int col = origemColuna - offset + j;

            // Verifica se está dentro dos limites
            if (lin >= 0 && lin < TAM && col >= 0 && col < TAM) {
                if (matriz[i][j] == 1 && tabuleiro[lin][col] == 0) {
                    tabuleiro[lin][col] = HABIL;
                }
            }
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("   ");
    for (int i = 0; i < TAM; i++)
        printf("%2d ", i);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM; j++) {
            int valor = tabuleiro[i][j];
            if (valor == 0)
                printf(" ~ "); // Água
            else if (valor == NAVIO)
                printf(" N "); // Navio
            else if (valor == HABIL)
                printf(" * "); // Habilidade
        }
        printf("\n");
    }
}

// Programa principal
int main() {
    int tabuleiro[TAM][TAM];
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);

    construirCone(cone);
    construirCruz(cruz);
    construirOctaedro(octaedro);

    // Aplicar habilidades em pontos centrais definidos
    aplicarHabilidade(tabuleiro, cone, 2, 2);
    aplicarHabilidade(tabuleiro, cruz, 5, 5);
    aplicarHabilidade(tabuleiro, octaedro, 7, 2);

    printf("\n=== TABULEIRO COM HABILIDADES ===\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
