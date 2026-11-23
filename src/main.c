#include <errno.h> /* Detecta erros na conversão do tamanho. */
#include <ctype.h> /* Permite transformar a primeira letra em maiúscula. */
#include <limits.h> /* Informa o maior valor permitido para int. */
#include <stdio.h> /* Permite imprimir mensagens. */
#include <stdlib.h> /* Fornece conversão, memória, aleatoriedade e códigos de saída. */
#include <string.h> /* Permite comparar nomes de algoritmos. */
#include <time.h> /* Permite medir tempo de CPU. */

#include "algoritmos.h" /* Importa as assinaturas das seis ordenações. */

typedef void (*Algoritmo)(int[], int, Metricas *); /* Define um ponteiro para qualquer algoritmo. */

typedef struct { /* Agrupa o nome e a função de cada opção. */
    const char *nome; /* Texto usado na linha de comando. */
    Algoritmo funcao; /* Endereço da função correspondente. */
} OpcaoAlgoritmo; /* Nome do tipo criado. */

static const OpcaoAlgoritmo algoritmos[] = { /* Tabela de algoritmos disponíveis. */
    {"bubble", bubbleSort},
    {"selection", selectionSort},
    {"insertion", insertionSort},
    {"merge", mergeSort},
    {"quick", quickSort},
    {"heap", heapSort}
};

static void uso(const char *programa) /* Mostra a forma correta de chamar o programa. */
{
    fprintf(stderr, "Uso: %s <n> [bubble|selection|insertion|merge|quick|heap]\n", programa);
}

static int converter_tamanho(const char *texto, int *resultado) /* Converte e valida o tamanho recebido. */
{
    char *fim; /* Recebe a posição onde a conversão parou. */
    long valor; /* Guarda temporariamente o número convertido. */

    errno = 0; /* Limpa o erro anterior antes de converter. */
    valor = strtol(texto, &fim, 10); /* Converte o texto usando base decimal. */
    if (errno != 0 || *texto == '\0' || *fim != '\0' || valor <= 0 || valor > INT_MAX) { /* Rejeita entradas inválidas. */
        return 0; /* Informa que a conversão falhou. */
    }

    *resultado = (int)valor; /* Copia o número convertido para o resultado. */
    return 1; /* Informa que a conversão funcionou. */
}

static void preencher_vetor(int *vetor, int n) /* Preenche o vetor original com números reproduzíveis. */
{
    int i; /* Índice da posição atual. */

    for (i = 0; i < n; i++) { /* Visita todas as posições. */
        vetor[i] = rand(); /* Gera e armazena um valor aleatório. */
    }
}

static void executar_algoritmo(const OpcaoAlgoritmo *opcao, const int *original, int n) /* Executa uma cópia independente. */
{
    int *copia; /* Vetor que o algoritmo poderá modificar. */
    Metricas metricas = {0}; /* Zera os contadores desta execução. */
    clock_t inicio; /* Momento em que a ordenação começa. */
    clock_t fim; /* Momento em que a ordenação termina. */
    double tempo_ms; /* Tempo convertido para milissegundos. */

    copia = malloc((size_t)n * sizeof(*copia)); /* Reserva espaço para a cópia. */
    if (copia == NULL) { /* Confere se a reserva funcionou. */
        fprintf(stderr, "Erro: nao foi possivel alocar uma copia.\n"); /* Explica a falha. */
        return; /* Evita usar um ponteiro inválido. */
    }
    memcpy(copia, original, (size_t)n * sizeof(*copia)); /* Copia antes da medição. */
    inicio = clock(); /* Começa a medir somente a função de ordenação. */
    opcao->funcao(copia, n, &metricas); /* Chama o algoritmo escolhido. */
    fim = clock(); /* Termina a medição. */
    tempo_ms = 1000.0 * (double)(fim - inicio) / (double)CLOCKS_PER_SEC; /* Converte ticks em ms. */
    printf("%c%s Sort\n", (char)toupper((unsigned char)opcao->nome[0]), opcao->nome + 1); /* Mostra o nome com aparência profissional. */
    printf("  Tempo        : %.3f ms\n", tempo_ms); /* Mostra o tempo em milissegundos. */
    printf("  Comparações  : %lu\n", metricas.comparacoes); /* Mostra o total de comparações. */
    printf("  Trocas       : %lu\n", metricas.trocas); /* Mostra o total de trocas. */
    free(copia); /* Libera o vetor de trabalho. */
}

static const OpcaoAlgoritmo *encontrar_algoritmo(const char *nome) /* Procura o algoritmo pelo nome. */
{
    size_t quantidade = sizeof(algoritmos) / sizeof(algoritmos[0]); /* Conta as opções da tabela. */
    size_t i; /* Índice usado na busca. */

    for (i = 0; i < quantidade; i++) { /* Visita cada opção. */
        if (strcmp(nome, algoritmos[i].nome) == 0) { /* Compara os dois textos. */
            return &algoritmos[i]; /* Devolve a opção encontrada. */
        }
    }
    return NULL; /* Informa que o nome não existe. */
}

int main(int argc, char *argv[]) /* Inicia a execução do programa. */
{
    int n; /* Tamanho solicitado pelo usuário. */
    int *vetor; /* Endereço do vetor reservado. */
    const OpcaoAlgoritmo *opcao; /* Algoritmo escolhido. */

    if (argc < 2 || argc > 3 || !converter_tamanho(argv[1], &n)) { /* Confere os argumentos. */
        uso(argv[0]); /* Mostra a forma correta de uso. */
        return EXIT_FAILURE; /* Sinaliza erro ao sistema. */
    }

    if (argc == 3) { /* Só entra aqui se um algoritmo foi informado. */
        opcao = encontrar_algoritmo(argv[2]); /* Procura o nome na tabela. */
        if (opcao == NULL) { /* Verifica se a busca falhou. */
            uso(argv[0]); /* Mostra os nomes válidos. */
            return EXIT_FAILURE; /* Encerra com erro. */
        }
    } else {
        opcao = NULL; /* Indica que serão processadas todas as opções disponíveis. */
    }

    vetor = malloc((size_t)n * sizeof(*vetor)); /* Reserva espaço para n inteiros. */
    if (n > 0 && vetor == NULL) { /* Confere se faltou memória. */
        fprintf(stderr, "Erro: nao foi possivel alocar o vetor.\n"); /* Explica a falha. */
        return EXIT_FAILURE; /* Encerra com erro. */
    }

    srand(42); /* Fixa a sequência aleatória para permitir repetição. */
    preencher_vetor(vetor, n); /* Cria uma entrada original compartilhada. */
    if (opcao != NULL) { /* Executa quando há algoritmo escolhido. */
        executar_algoritmo(opcao, vetor, n); /* Mede uma cópia do vetor original. */
    } else {
        size_t quantidade = sizeof(algoritmos) / sizeof(algoritmos[0]); /* Conta as opções disponíveis. */
        size_t i; /* Índice da opção atual. */
        for (i = 0; i < quantidade; i++) { /* Executa todos os algoritmos. */
            executar_algoritmo(&algoritmos[i], vetor, n); /* Cada chamada recebe uma cópia independente. */
        }
    }

    free(vetor); /* Libera a memória reservada. */
    return EXIT_SUCCESS; /* Encerra com sucesso. */
}
