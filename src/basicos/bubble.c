#include "../algoritmos.h" /* Importa a assinatura e o tipo de métricas. */

void bubbleSort(int v[], int n, Metricas *m) /* Função pública do Bubble Sort. */
{
    int i; /* Controla as passadas pelo vetor. */
    int j; /* Controla a comparação entre vizinhos. */

    if (n <= 1) { /* Vetores vazios ou unitários já estão ordenados. */
        return; /* Sai sem acessar posições inválidas. */
    }

    for (i = 0; i < n - 1; i++) { /* Faz todas as passadas da versão clássica. */
        for (j = 0; j < n - 1 - i; j++) { /* Compara vizinhos ainda não posicionados. */
            m->comparacoes++; /* Conta somente a comparação entre dois valores. */
            if (v[j] > v[j + 1]) { /* Verifica se os vizinhos estão invertidos. */
                int temporario = v[j]; /* Guarda o primeiro valor durante a troca. */
                v[j] = v[j + 1]; /* Move o menor valor para a esquerda. */
                v[j + 1] = temporario; /* Move o maior valor para a direita. */
                m->trocas++; /* Conta uma permuta efetiva. */
            }
        }
    }
}
