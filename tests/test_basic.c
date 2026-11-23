#include <stdio.h> /* Permite escrever o resultado dos testes. */
#include <string.h> /* Permite comparar vetores byte a byte. */

#include "algoritmos.h" /* Importa o Bubble Sort e o tipo Metricas. */

typedef void (*Algoritmo)(int[], int, Metricas *); /* Tipo para receber qualquer função de ordenação. */

static int vetor_igual(const int *a, const int *b, int n) /* Compara duas listas de inteiros. */
{
    int i; /* Índice da posição examinada. */

    for (i = 0; i < n; i++) { /* Verifica cada elemento. */
        if (a[i] != b[i]) { /* Detecta qualquer diferença. */
            return 0; /* Informa que os vetores são diferentes. */
        }
    }
    return 1; /* Informa que todos os elementos são iguais. */
}

static int testar_bubble(const char *nome, const int *entrada, const int *esperado, int n, unsigned long comparacoes_minimas) /* Executa um caso. */
{
    int vetor[10]; /* Reserva um espaço suficiente para os casos atuais. */
    Metricas metricas = {0}; /* Começa os contadores zerados. */

    memcpy(vetor, entrada, (size_t)n * sizeof(vetor[0])); /* Copia a entrada para preservar o original. */
    bubbleSort(vetor, n, &metricas); /* Executa o algoritmo testado. */
    if (!vetor_igual(vetor, esperado, n) || metricas.comparacoes != comparacoes_minimas) { /* Confere saída e comparações. */
        printf("FALHOU: %s\n", nome); /* Informa o caso que falhou. */
        return 1; /* Sinaliza falha para o Makefile. */
    }
    printf("PASSOU: %s\n", nome); /* Informa que o caso passou. */
    return 0; /* Sinaliza sucesso. */
}

static int testar_algoritmo(const char *nome, Algoritmo algoritmo, const int *entrada, const int *esperado, int n, long comparacoes_esperadas) /* Testa Selection ou Insertion. */
{
    int vetor[10]; /* Reserva espaço para os casos pequenos. */
    Metricas metricas = {0}; /* Zera os contadores antes da chamada. */

    memcpy(vetor, entrada, (size_t)n * sizeof(vetor[0])); /* Copia a entrada para não alterá-la. */
    algoritmo(vetor, n, &metricas); /* Chama o algoritmo recebido. */
    if (!vetor_igual(vetor, esperado, n)) { /* Confere se a saída está ordenada corretamente. */
        printf("FALHOU: %s\n", nome); /* Informa a falha de ordenação. */
        return 1; /* Sinaliza falha. */
    }
    if (comparacoes_esperadas >= 0 && metricas.comparacoes != (unsigned long)comparacoes_esperadas) { /* Confere a métrica quando definida. */
        printf("FALHOU: %s (comparacoes)\n", nome); /* Informa a falha de métrica. */
        return 1; /* Sinaliza falha. */
    }
    printf("PASSOU: %s\n", nome); /* Informa que o caso passou. */
    return 0; /* Sinaliza sucesso. */
}

int main(void) /* Ponto de entrada provisório dos testes. */
{
    const int caso_misto[] = {5, 3, 8, 4, 2}; /* Entrada principal do enunciado da fase. */
    const int esperado_misto[] = {2, 3, 4, 5, 8}; /* Resultado ordenado esperado. */
    const int caso_duplicado[] = {3, 1, 3, 2, 1}; /* Entrada com valores repetidos. */
    const int esperado_duplicado[] = {1, 1, 2, 3, 3}; /* Resultado que preserva duplicatas. */
    const int caso_ordenado[] = {1, 2, 3, 4}; /* Entrada que já está ordenada. */
    const int caso_inverso[] = {4, 3, 2, 1}; /* Entrada em ordem decrescente. */
    const int esperado_inverso[] = {1, 2, 3, 4}; /* Resultado do caso inverso. */
    const int caso_vazio[] = {}; /* Vetor sem elementos. */
    const int caso_unico[] = {7}; /* Vetor com um único elemento. */
    int falhas = 0; /* Soma quantos casos falharam. */

    falhas += testar_bubble("Bubble com vetor misto", caso_misto, esperado_misto, 5, 10); /* 5*4/2 comparações. */
    falhas += testar_bubble("Bubble com duplicatas", caso_duplicado, esperado_duplicado, 5, 10); /* 5*4/2 comparações. */
    falhas += testar_bubble("Bubble com vetor ordenado", caso_ordenado, caso_ordenado, 4, 6); /* 4*3/2 comparações. */
    falhas += testar_bubble("Bubble com vetor inverso", caso_inverso, esperado_inverso, 4, 6); /* 4*3/2 comparações. */
    falhas += testar_bubble("Bubble com vetor vazio", caso_vazio, caso_vazio, 0, 0); /* Não acessa posições. */
    falhas += testar_bubble("Bubble com vetor unitario", caso_unico, caso_unico, 1, 0); /* Já está ordenado. */
    falhas += testar_algoritmo("Selection com vetor misto", selectionSort, caso_misto, esperado_misto, 5, 10); /* Selection compara n(n-1)/2 vezes. */
    falhas += testar_algoritmo("Selection com duplicatas", selectionSort, caso_duplicado, esperado_duplicado, 5, 10); /* Duplicatas são preservadas. */
    falhas += testar_algoritmo("Selection com vetor crescente", selectionSort, caso_ordenado, caso_ordenado, 4, 6); /* Testa entrada crescente. */
    falhas += testar_algoritmo("Selection com vetor decrescente", selectionSort, caso_inverso, esperado_inverso, 4, 6); /* Testa entrada decrescente. */
    falhas += testar_algoritmo("Selection com vetor vazio", selectionSort, caso_vazio, caso_vazio, 0, 0); /* Não acessa posições inválidas. */
    falhas += testar_algoritmo("Insertion com vetor misto", insertionSort, caso_misto, esperado_misto, 5, -1); /* Verifica ordenação e movimentações. */
    falhas += testar_algoritmo("Insertion com vetor crescente", insertionSort, caso_ordenado, caso_ordenado, 4, -1); /* Representa o melhor caso. */
    falhas += testar_algoritmo("Insertion com vetor inverso", insertionSort, caso_inverso, esperado_inverso, 4, -1); /* Representa muitas movimentações. */
    falhas += testar_algoritmo("Insertion com duplicatas", insertionSort, caso_duplicado, esperado_duplicado, 5, -1); /* Confere valores repetidos. */
    falhas += testar_algoritmo("Insertion com vetor vazio", insertionSort, caso_vazio, caso_vazio, 0, 0); /* Não acessa posições inválidas. */
    falhas += testar_algoritmo("Insertion com vetor unitario", insertionSort, caso_unico, caso_unico, 1, 0); /* Caso-base. */
    return falhas == 0 ? 0 : 1; /* Retorna erro se algum teste falhou. */
}
