#ifndef METRICAS_H /* Evita que este arquivo seja incluído duas vezes. */
#define METRICAS_H /* Marca que o cabeçalho já foi carregado. */

typedef struct { /* Cria um tipo que agrupa os contadores do algoritmo. */
    unsigned long comparacoes; /* Guarda quantas comparações de valores ocorreram. */
    unsigned long trocas; /* Guarda quantas trocas ou movimentações ocorreram. */
} Metricas; /* Dá o nome Metricas para essa estrutura. */

#endif /* Finaliza a proteção contra inclusão repetida. */
