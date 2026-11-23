#include "../algoritmos.h" /* Importa o contrato das funções de ordenação. */

void selectionSort(int v[], int n, Metricas *m) /* Função pública do Selection Sort. */
{
    int i; /* Posição que receberá o menor elemento restante. */

    for (i = 0; i < n - 1; i++) { /* Percorre as posições que serão preenchidas. */
        int menor = i; /* Assume inicialmente que o primeiro restante é o menor. */
        int j; /* Índice usado para procurar um valor menor. */

        for (j = i + 1; j < n; j++) { /* Procura no restante do vetor. */
            m->comparacoes++; /* Conta somente a comparação entre dois valores. */
            if (v[j] < v[menor]) { /* Verifica se encontrou um novo menor. */
                menor = j; /* Guarda a posição do novo menor valor. */
            }
        }

        if (menor != i) { /* Evita trocar um elemento consigo mesmo. */
            int temporario = v[i]; /* Guarda o valor da posição atual. */
            v[i] = v[menor]; /* Coloca o menor valor na posição correta. */
            v[menor] = temporario; /* Coloca o valor antigo na posição encontrada. */
            m->trocas++; /* Conta a permuta efetiva. */
        }
    }
}
