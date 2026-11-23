#include <stdio.h> /* Permite escrever o resultado dos testes. */
#include <stdlib.h> /* Permite alocar memória e gerar valores de teste. */
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

static int vetor_ordenado(const int *vetor, int n) /* Confere se cada valor não é maior que o próximo. */
{
    int i; /* Índice da comparação atual. */

    for (i = 1; i < n; i++) { /* Começa no segundo elemento. */
        if (vetor[i - 1] > vetor[i]) { /* Detecta uma inversão. */
            return 0; /* Informa que o vetor ainda não está ordenado. */
        }
    }
    return 1; /* Informa que o vetor está em ordem não decrescente. */
}

static int testar_quick_grande(const char *nome, int *vetor, int n) /* Testa Quick em uma entrada maior. */
{
    Metricas metricas = {0}; /* Zera as métricas antes da execução. */

    quickSort(vetor, n, &metricas); /* Ordena a entrada grande. */
    if (!vetor_ordenado(vetor, n)) { /* Confere o resultado completo. */
        printf("FALHOU: %s\n", nome); /* Informa a falha. */
        return 1; /* Sinaliza erro. */
    }
    printf("PASSOU: %s (%d elementos)\n", nome, n); /* Informa o sucesso. */
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
    falhas += testar_algoritmo("Merge com vetor misto", mergeSort, caso_misto, esperado_misto, 5, -1); /* Testa tamanho ímpar. */
    falhas += testar_algoritmo("Merge com duplicatas", mergeSort, caso_duplicado, esperado_duplicado, 5, -1); /* Confere estabilidade de valores iguais. */
    falhas += testar_algoritmo("Merge com vetor crescente", mergeSort, caso_ordenado, caso_ordenado, 4, -1); /* Testa tamanho par. */
    falhas += testar_algoritmo("Merge com vetor decrescente", mergeSort, caso_inverso, esperado_inverso, 4, -1); /* Testa intercalação completa. */
    falhas += testar_algoritmo("Merge com vetor vazio", mergeSort, caso_vazio, caso_vazio, 0, 0); /* Caso-base vazio. */
    falhas += testar_algoritmo("Merge com vetor unitario", mergeSort, caso_unico, caso_unico, 1, 0); /* Caso-base unitário. */
    falhas += testar_algoritmo("Quick com vetor misto", quickSort, caso_misto, esperado_misto, 5, -1); /* Testa partição central. */
    falhas += testar_algoritmo("Quick com duplicatas", quickSort, caso_duplicado, esperado_duplicado, 5, -1); /* Testa avanço com repetidos. */
    falhas += testar_algoritmo("Quick com vetor crescente", quickSort, caso_ordenado, caso_ordenado, 4, -1); /* Testa padrão crescente. */
    falhas += testar_algoritmo("Quick com vetor decrescente", quickSort, caso_inverso, esperado_inverso, 4, -1); /* Testa padrão decrescente. */
    falhas += testar_algoritmo("Quick com vetor vazio", quickSort, caso_vazio, caso_vazio, 0, 0); /* Caso-base vazio. */
    falhas += testar_algoritmo("Quick com vetor unitario", quickSort, caso_unico, caso_unico, 1, 0); /* Caso-base unitário. */
    {
        const int caso_iguais[] = {5, 5, 5, 5}; /* Entrada em que todos os valores são iguais. */
        falhas += testar_algoritmo("Quick com valores iguais", quickSort, caso_iguais, caso_iguais, 4, -1); /* Evita laço infinito. */
    }
    {
        const int tamanho_grande = 10000; /* Tamanho suficiente para exercitar a recursão. */
        int *aleatorio = malloc((size_t)tamanho_grande * sizeof(*aleatorio)); /* Reserva a entrada aleatória. */
        int *crescente = malloc((size_t)tamanho_grande * sizeof(*crescente)); /* Reserva a entrada crescente. */
        int *decrescente = malloc((size_t)tamanho_grande * sizeof(*decrescente)); /* Reserva a entrada decrescente. */
        int *repetido = malloc((size_t)tamanho_grande * sizeof(*repetido)); /* Reserva a entrada repetida. */
        int i; /* Índice para preencher as entradas. */

        if (aleatorio == NULL || crescente == NULL || decrescente == NULL || repetido == NULL) { /* Confere todas as alocações. */
            free(aleatorio); /* Libera a primeira entrada. */
            free(crescente); /* Libera a segunda entrada. */
            free(decrescente); /* Libera a terceira entrada. */
            free(repetido); /* Libera a quarta entrada. */
            fprintf(stderr, "FALHOU: alocacao dos testes grandes\n"); /* Informa a falha de memória. */
            return 1; /* Encerra os testes com erro. */
        }

        srand(42); /* Torna os valores aleatórios reproduzíveis. */
        for (i = 0; i < tamanho_grande; i++) { /* Preenche todas as entradas. */
            aleatorio[i] = rand(); /* Cria um padrão aleatório. */
            crescente[i] = i; /* Cria um padrão crescente. */
            decrescente[i] = tamanho_grande - i; /* Cria um padrão decrescente. */
            repetido[i] = i % 7; /* Cria muitos valores repetidos. */
        }

        falhas += testar_quick_grande("Quick aleatorio", aleatorio, tamanho_grande); /* Testa entrada aleatória. */
        falhas += testar_quick_grande("Quick crescente", crescente, tamanho_grande); /* Testa entrada crescente. */
        falhas += testar_quick_grande("Quick decrescente", decrescente, tamanho_grande); /* Testa entrada decrescente. */
        falhas += testar_quick_grande("Quick repetido", repetido, tamanho_grande); /* Testa valores repetidos. */
        free(aleatorio); /* Libera a entrada aleatória. */
        free(crescente); /* Libera a entrada crescente. */
        free(decrescente); /* Libera a entrada decrescente. */
        free(repetido); /* Libera a entrada repetida. */
    }
    falhas += testar_algoritmo("Heap com vetor misto", heapSort, caso_misto, esperado_misto, 5, -1); /* Testa tamanho ímpar. */
    falhas += testar_algoritmo("Heap com duplicatas", heapSort, caso_duplicado, esperado_duplicado, 5, -1); /* Preserva valores repetidos. */
    falhas += testar_algoritmo("Heap com vetor crescente", heapSort, caso_ordenado, caso_ordenado, 4, -1); /* Testa tamanho par. */
    falhas += testar_algoritmo("Heap com vetor decrescente", heapSort, caso_inverso, esperado_inverso, 4, -1); /* Testa extrações. */
    falhas += testar_algoritmo("Heap com vetor vazio", heapSort, caso_vazio, caso_vazio, 0, 0); /* Caso-base vazio. */
    falhas += testar_algoritmo("Heap com vetor unitario", heapSort, caso_unico, caso_unico, 1, 0); /* Caso-base unitário. */
    return falhas == 0 ? 0 : 1; /* Retorna erro se algum teste falhou. */
}
