#include <stdio.h> /* Permite escrever o CSV e mensagens de erro. */
#include <stdlib.h> /* Permite alocar, liberar e gerar memória. */
#include <string.h> /* Permite copiar a entrada antes de cada repetição. */
#include <time.h> /* Fornece clock para medir tempo de CPU. */

#include "algoritmos.h" /* Importa as seis funções de ordenação. */

typedef void (*Algoritmo)(int[], int, Metricas *); /* Tipo para apontar para qualquer algoritmo. */

typedef struct { /* Associa o nome do algoritmo à função correspondente. */
    const char *nome; /* Nome usado na primeira coluna do CSV. */
    Algoritmo funcao; /* Função chamada durante a medição. */
    int permite_500000; /* Indica se o algoritmo pode usar o maior tamanho. */
} OpcaoAlgoritmo; /* Nome do tipo criado. */

static const OpcaoAlgoritmo algoritmos[] = { /* Tabela exigida pelo protocolo. */
    {"bubble", bubbleSort, 0}, /* Bubble não recebe n=500000. */
    {"selection", selectionSort, 0}, /* Selection não recebe n=500000. */
    {"insertion", insertionSort, 0}, /* Insertion não recebe n=500000. */
    {"merge", mergeSort, 1}, /* Merge recebe todos os tamanhos. */
    {"quick", quickSort, 1}, /* Quick recebe todos os tamanhos. */
    {"heap", heapSort, 1} /* Heap recebe todos os tamanhos. */
};

static const char *tipos[] = {"aleatorio", "crescente", "decrescente"}; /* Tipos de entrada. */
static const int tamanhos[] = {1000, 5000, 10000, 50000, 500000}; /* Tamanhos possíveis. */

static void gerar_entrada(int *vetor, int n, int tipo) /* Gera uma entrada original. */
{
    int i; /* Índice usado para preencher o vetor. */

    for (i = 0; i < n; i++) { /* Visita cada posição uma vez. */
        if (tipo == 0) { /* Cria valores aleatórios reproduzíveis. */
            vetor[i] = rand(); /* Usa a semente definida em main. */
        } else if (tipo == 1) { /* Cria uma sequência crescente. */
            vetor[i] = i; /* O índice já está na ordem desejada. */
        } else { /* Cria uma sequência decrescente. */
            vetor[i] = n - i; /* O primeiro valor é o maior. */
        }
    }
}

static int esta_ordenado(const int *vetor, int n) /* Confere a ordem não decrescente. */
{
    int i; /* Índice da posição examinada. */

    for (i = 1; i < n; i++) { /* Compara cada elemento com o anterior. */
        if (vetor[i - 1] > vetor[i]) { /* Detecta uma inversão. */
            return 0; /* Informa que a saída está incorreta. */
        }
    }
    return 1; /* Informa que a saída está ordenada. */
}

static int executar_combinacao(const OpcaoAlgoritmo *algoritmo, const char *tipo, int n) /* Mede uma combinação completa. */
{
    const int repeticoes = 5; /* O protocolo exige cinco execuções. */
    int *original = malloc((size_t)n * sizeof(*original)); /* Reserva a entrada original. */
    int *trabalho = malloc((size_t)n * sizeof(*trabalho)); /* Reserva a cópia de trabalho. */
    double tempo_total = 0.0; /* Acumula os cinco tempos. */
    Metricas metricas = {0}; /* Guarda as métricas da última execução válida. */
    int tipo_numero; /* Guarda o índice do tipo textual. */
    int repeticao; /* Controla as cinco repetições. */

    if (original == NULL || trabalho == NULL) { /* Confere as duas reservas. */
        fprintf(stderr, "Erro: memoria insuficiente para %s n=%d.\n", algoritmo->nome, n); /* Informa a combinação. */
        free(original); /* Libera a primeira reserva. */
        free(trabalho); /* Libera a segunda reserva. */
        return 0; /* Indica falha. */
    }

    for (tipo_numero = 0; tipo_numero < 3; tipo_numero++) { /* Localiza o texto do tipo recebido. */
        if (strcmp(tipo, tipos[tipo_numero]) == 0) { /* Compara os nomes. */
            break; /* Para ao encontrar o tipo. */
        }
    }
    gerar_entrada(original, n, tipo_numero); /* Gera uma vez para todas as repetições. */

    for (repeticao = 0; repeticao < repeticoes; repeticao++) { /* Repete a medição cinco vezes. */
        clock_t inicio; /* Momento anterior à chamada de ordenação. */
        clock_t fim; /* Momento posterior à chamada de ordenação. */

        memcpy(trabalho, original, (size_t)n * sizeof(*trabalho)); /* Copia antes de iniciar o relógio. */
        metricas = (Metricas){0}; /* Zera as métricas desta repetição. */
        inicio = clock(); /* Começa a medir apenas a ordenação. */
        algoritmo->funcao(trabalho, n, &metricas); /* Executa o algoritmo. */
        fim = clock(); /* Para a medição imediatamente após a ordenação. */
        if (!esta_ordenado(trabalho, n)) { /* Confere a saída fora do tempo medido. */
            fprintf(stderr, "Erro: %s produziu saida incorreta para %s n=%d.\n", algoritmo->nome, tipo, n); /* Informa o erro. */
            free(original); /* Libera a entrada original. */
            free(trabalho); /* Libera o vetor de trabalho. */
            return 0; /* Impede a publicação de uma linha inválida. */
        }
        tempo_total += 1000.0 * (double)(fim - inicio) / (double)CLOCKS_PER_SEC; /* Soma milissegundos. */
    }

    printf("%s,%s,%d,%.3f,%lu,%lu\n", algoritmo->nome, tipo, n, tempo_total / repeticoes, metricas.comparacoes, metricas.trocas); /* Grava uma linha média. */
    free(original); /* Libera a entrada original. */
    free(trabalho); /* Libera a cópia de trabalho. */
    return 1; /* Indica sucesso. */
}

int main(void) /* Inicia o benchmark completo. */
{
    size_t algoritmo_indice; /* Índice da tabela de algoritmos. */
    int tipo; /* Índice do tipo de entrada. */
    size_t tamanho_indice; /* Índice da tabela de tamanhos. */
    size_t quantidade_algoritmos = sizeof(algoritmos) / sizeof(algoritmos[0]); /* Conta os algoritmos. */
    size_t quantidade_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]); /* Conta os tamanhos. */

    srand(42); /* Fixa a entrada aleatória para permitir reprodução. */
    printf("algoritmo,tipo,n,tempo_ms,comparacoes,trocas\n"); /* Imprime o cabeçalho exato. */
    for (algoritmo_indice = 0; algoritmo_indice < quantidade_algoritmos; algoritmo_indice++) { /* Percorre algoritmos. */
        for (tipo = 0; tipo < 3; tipo++) { /* Percorre os três tipos de entrada. */
            for (tamanho_indice = 0; tamanho_indice < quantidade_tamanhos; tamanho_indice++) { /* Percorre tamanhos. */
                int n = tamanhos[tamanho_indice]; /* Obtém o tamanho atual. */
                if (n == 500000 && !algoritmos[algoritmo_indice].permite_500000) { /* Pula o maior tamanho nos básicos. */
                    continue; /* Mantém o protocolo em 81 combinações. */
                }
                if (!executar_combinacao(&algoritmos[algoritmo_indice], tipos[tipo], n)) { /* Mede e valida. */
                    return EXIT_FAILURE; /* Falha sem gerar resultado incompleto. */
                }
            }
        }
    }
    return EXIT_SUCCESS; /* Finaliza após as 405 ordenações. */
}
