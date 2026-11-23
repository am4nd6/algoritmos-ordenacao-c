#include <stdlib.h> /* Fornece malloc, free e NULL para a memória auxiliar. */

#include "../algoritmos.h" /* Importa o contrato e o tipo Metricas. */

static void intercalar(int v[], int auxiliar[], int inicio, int meio, int fim, Metricas *m) /* Junta duas partes já ordenadas. */
{
    int esquerda = inicio; /* Primeiro índice da metade esquerda. */
    int direita = meio + 1; /* Primeiro índice da metade direita. */
    int destino = inicio; /* Posição que receberá o próximo menor valor. */

    while (esquerda <= meio && direita <= fim) { /* Continua enquanto as duas metades têm valores. */
        m->comparacoes++; /* Conta a comparação entre os dois valores candidatos. */
        if (v[esquerda] <= v[direita]) { /* Escolhe a esquerda em empate para manter estabilidade. */
            auxiliar[destino] = v[esquerda]; /* Copia o valor esquerdo para o buffer. */
            esquerda++; /* Avança na metade esquerda. */
        } else {
            auxiliar[destino] = v[direita]; /* Copia o valor direito para o buffer. */
            direita++; /* Avança na metade direita. */
        }
        m->trocas++; /* Conta a cópia feita no buffer auxiliar. */
        destino++; /* Avança a posição de destino. */
    }

    while (esquerda <= meio) { /* Copia os valores restantes da esquerda. */
        auxiliar[destino] = v[esquerda]; /* Transfere o valor restante. */
        esquerda++; /* Avança na metade esquerda. */
        destino++; /* Avança no buffer. */
        m->trocas++; /* Conta a cópia. */
    }

    while (direita <= fim) { /* Copia os valores restantes da direita. */
        auxiliar[destino] = v[direita]; /* Transfere o valor restante. */
        direita++; /* Avança na metade direita. */
        destino++; /* Avança no buffer. */
        m->trocas++; /* Conta a cópia. */
    }

    for (destino = inicio; destino <= fim; destino++) { /* Devolve a parte ordenada ao vetor original. */
        v[destino] = auxiliar[destino]; /* Copia o resultado para o vetor do chamador. */
        m->trocas++; /* Conta a cópia de retorno. */
    }
}

static void ordenar_intervalo(int v[], int auxiliar[], int inicio, int fim, Metricas *m) /* Ordena um intervalo recursivamente. */
{
    int meio; /* Índice que divide o intervalo em duas partes. */

    if (inicio >= fim) { /* Um intervalo com zero ou um elemento já está ordenado. */
        return; /* Encerra a recursão sem acessar fora do vetor. */
    }

    meio = inicio + (fim - inicio) / 2; /* Calcula o meio sem somar índices grandes diretamente. */
    ordenar_intervalo(v, auxiliar, inicio, meio, m); /* Ordena a metade esquerda. */
    ordenar_intervalo(v, auxiliar, meio + 1, fim, m); /* Ordena a metade direita. */
    intercalar(v, auxiliar, inicio, meio, fim, m); /* Intercala as duas metades. */
}

void mergeSort(int v[], int n, Metricas *m) /* Função pública do Merge Sort. */
{
    int *auxiliar; /* Buffer usado para intercalar as partes. */

    if (n <= 1) { /* Vetores vazios ou unitários já estão ordenados. */
        return; /* Evita alocação e acesso inválido. */
    }

    auxiliar = malloc((size_t)n * sizeof(*auxiliar)); /* Aloca o buffer dentro da função pública. */
    if (auxiliar == NULL) { /* Confere falha de memória antes de usar o buffer. */
        return; /* Mantém o vetor original intacto em caso de falha. */
    }

    ordenar_intervalo(v, auxiliar, 0, n - 1, m); /* Divide, ordena e intercala todo o vetor. */
    free(auxiliar); /* Libera o buffer antes de retornar. */
}
