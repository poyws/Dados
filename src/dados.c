#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define MAX_DADOS 10
#define MAX_RODADAS 100
#define MAX_FACES 20

void limparTela() {
    printf("\033[H\033[J");
}

void atraso(int segundos) {
    sleep(segundos);
}

void exibirEstatisticas(int rodadas, int maiorValor, int menorValor, int somaTotal, float media) {
    printf("\n--- Estatísticas ---\n");
    printf("Rodadas Jogadas: %d\n", rodadas);
    printf("Maior Valor: %d\n", maiorValor);
    printf("Menor Valor: %d\n", menorValor);
    printf("Soma Total: %d\n", somaTotal);
    printf("Média: %.2f\n", media);
}

void salvarEstatisticas(int maiorValor, int menorValor, int somaTotal, float media) {
    FILE *arquivo = fopen("estatisticas_jogo.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar estatísticas!\n");
        return;
    }
    fprintf(arquivo, "Maior Valor: %d\nMenor Valor: %d\nSoma Total: %d\nMédia: %.2f\n",
            maiorValor, menorValor, somaTotal, media);
    fclose(arquivo);
}

int main() {
    int numDados, numRodadas, i, j;
    int maiorValor = 0, menorValor = 7;
    char jogarNovamente;
    int somaTotal = 0;

    do {
        limparTela();
        
        printf("Digite a quantidade de dados (1 a %d): ", MAX_DADOS);
        while (scanf("%d", &numDados) != 1 || numDados < 1 || numDados > MAX_DADOS) {
            printf("Valor inválido. Digite a quantidade de dados (1 a %d): ", MAX_DADOS);
            while(getchar() != '\n');
        }

        printf("Digite o número de rodadas (1 a %d): ", MAX_RODADAS);
        while (scanf("%d", &numRodadas) != 1 || numRodadas < 1 || numRodadas > MAX_RODADAS) {
            printf("Valor inválido. Digite o número de rodadas (1 a %d): ", MAX_RODADAS);
            while(getchar() != '\n');
        }

        int facesDados;
        printf("Digite a quantidade de faces dos dados (4, 6, 8, 10, 12, 20): ");
        while (scanf("%d", &facesDados) != 1 || (facesDados != 4 && facesDados != 6 && facesDados != 8 && facesDados != 10 && facesDados != 12 && facesDados != 20)) {
            printf("Valor inválido. Digite a quantidade de faces dos dados (4, 6, 8, 10, 12, 20): ");
            while(getchar() != '\n');
        }

        srand(time(NULL));
        printf("\nResultados:\n");
        printf("Rodada\t");
        for (i = 1; i <= numDados; i++) {
            printf("Dado %d\t", i);
        }
        printf("Soma\n");

        for (i = 1; i <= numRodadas; i++) {
            int soma = 0;
            printf("%d\t", i);
            for (j = 0; j < numDados; j++) {
                int resultado = (rand() % facesDados) + 1;
                printf("%d\t", resultado);
                soma += resultado;

                if (resultado > maiorValor) maiorValor = resultado;
                if (resultado < menorValor) menorValor = resultado;
            }
            somaTotal += soma;
            printf("%d\n", soma);
            atraso(1);
        }

        float media = (float)somaTotal / numRodadas;
        exibirEstatisticas(numRodadas, maiorValor, menorValor, somaTotal, media);
        salvarEstatisticas(maiorValor, menorValor, somaTotal, media);

        printf("Deseja jogar novamente? (s/n): ");
        scanf(" %c", &jogarNovamente);
    } while (jogarNovamente == 's' || jogarNovamente == 'S');

    return 0;
}
