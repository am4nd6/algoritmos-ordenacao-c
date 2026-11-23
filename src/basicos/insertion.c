#include "../algoritmos.h" /* Importa o contrato comum dos algoritmos. */

void insertionSort(int v[], int n, Metricas *m) /* Função pública do Insertion Sort. */
{
    int i; /* Índice da chave que será inserida. */

    for (i = 1; i < n; i++) { /* O primeiro elemento sozinho já forma um prefixo ordenado. */
        int chave = v[i]; /* Guarda o valor que será inserido. */
        int j = i - 1; /* Começa comparando com o último elemento do prefixo. */

        while (j >= 0) { /* Continua enquanto ainda houver posição para comparar. */
            m->comparacoes++; /* Conta a comparação entre o prefixo e a chave. */
            if (v[j] <= chave) { /* Para quando a chave já está após um valor menor ou igual. */
                break; /* Evita deslocar elementos que já estão na ordem certa. */
            }
            v[j + 1] = v[j]; /* Desloca o valor maior uma posição para a direita. */
            m->trocas++; /* Conta o deslocamento como movimentação. */
            j--; /* Avança para a posição anterior do prefixo. */
        }
        v[j + 1] = chave; /* Insere a chave na posição encontrada. */
        m->trocas++; /* Conta a cópia da chave para sua posição final. */
    }
}
