#include "../algoritmos.h" /* Importa o contrato comum dos algoritmos. */

static int particionar(int v[], int inicio, int fim, Metricas *m) /* Divide o intervalo em torno de um pivô central. */
{
    int i = inicio; /* Caminha da esquerda para a direita. */
    int j = fim; /* Caminha da direita para a esquerda. */
    int pivo = v[inicio + (fim - inicio) / 2]; /* Escolhe o elemento do meio como pivô. */

    while (i <= j) { /* Continua até os índices se cruzarem. */
        while (1) { /* Procura um valor que deve ficar depois do pivô. */
            m->comparacoes++; /* Conta a comparação entre um valor e o pivô. */
            if (!(v[i] < pivo)) { /* Para quando o valor não é menor que o pivô. */
                break; /* Evita ultrapassar a posição correta. */
            }
            i++; /* Avança o índice esquerdo. */
        }
        while (1) { /* Procura um valor que deve ficar antes do pivô. */
            m->comparacoes++; /* Conta a comparação entre um valor e o pivô. */
            if (!(v[j] > pivo)) { /* Para quando o valor não é maior que o pivô. */
                break; /* Evita ultrapassar a posição correta. */
            }
            j--; /* Recuo do índice direito. */
        }
        if (i <= j) { /* Os dois valores podem ser corrigidos ou são iguais ao pivô. */
            if (i != j) { /* Evita contabilizar troca de uma posição consigo mesma. */
                int temporario = v[i]; /* Guarda o valor esquerdo. */
                v[i] = v[j]; /* Coloca o valor direito à esquerda. */
                v[j] = temporario; /* Coloca o valor esquerdo à direita. */
                m->trocas++; /* Conta a permuta efetiva. */
            }
            i++; /* Garante avanço mesmo com valores repetidos. */
            j--; /* Garante redução do intervalo. */
        }
    }
    return i; /* Retorna o primeiro índice da parte direita. */
}

static void ordenar_intervalo(int v[], int inicio, int fim, Metricas *m) /* Ordena recursivamente um intervalo. */
{
    int proxima; /* Ponto que separa as duas partes. */

    if (inicio >= fim) { /* Um intervalo de até um elemento já está ordenado. */
        return; /* Encerra a recursão. */
    }
    proxima = particionar(v, inicio, fim, m); /* Divide o intervalo pelo pivô central. */
    ordenar_intervalo(v, inicio, proxima - 1, m); /* Ordena a parte esquerda. */
    ordenar_intervalo(v, proxima, fim, m); /* Ordena a parte direita. */
}

void quickSort(int v[], int n, Metricas *m) /* Função pública do Quick Sort. */
{
    if (n <= 1) { /* Vetores vazios ou unitários já estão ordenados. */
        return; /* Evita acessar posições inválidas. */
    }
    ordenar_intervalo(v, 0, n - 1, m); /* Ordena o vetor inteiro. */
}
