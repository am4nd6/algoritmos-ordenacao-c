#include "../algoritmos.h" /* Importa o contrato dos algoritmos. */

void heapSort(int v[], int n, Metricas *m) /* Função pública do Heap Sort. */
{
    int inicio; /* Índice usado para construir o heap. */
    int fim; /* Último índice da região ainda não ordenada. */

    if (n <= 1) { /* Vetores vazios ou unitários já estão ordenados. */
        return; /* Evita acessar posições inválidas. */
    }

    for (inicio = n / 2 - 1; inicio >= 0; inicio--) { /* Ajusta cada pai para construir o max-heap. */
        int raiz = inicio; /* Começa o ajuste pela raiz do subárvore. */
        while (2 * raiz + 1 < n) { /* Continua enquanto existir filho esquerdo. */
            int maior = 2 * raiz + 1; /* Calcula o índice do filho esquerdo. */
            int direito = maior + 1; /* Calcula o índice do filho direito. */

            m->comparacoes++; /* Compara o filho direito com o maior candidato. */
            if (direito < n && v[direito] > v[maior]) { /* Escolhe o maior filho dentro do limite. */
                maior = direito; /* Atualiza o índice do maior filho. */
            }
            m->comparacoes++; /* Compara o maior filho com a raiz atual. */
            if (v[raiz] >= v[maior]) { /* O heap já está correto neste caminho. */
                break; /* Encerra o ajuste. */
            }
            {
                int temporario = v[raiz]; /* Guarda a raiz durante a troca. */
                v[raiz] = v[maior]; /* Coloca o maior valor na raiz. */
                v[maior] = temporario; /* Move a raiz antiga para o filho. */
                m->trocas++; /* Conta a permuta efetiva. */
            }
            raiz = maior; /* Continua ajustando a posição para baixo. */
        }
    }

    for (fim = n - 1; fim > 0; fim--) { /* Retira o maior elemento a cada passagem. */
        int temporario = v[0]; /* Guarda a raiz do heap. */
        v[0] = v[fim]; /* Move o último elemento para a raiz. */
        v[fim] = temporario; /* Coloca o maior elemento na posição final. */
        m->trocas++; /* Conta a permuta de extração. */

        {
            int raiz = 0; /* Reinicia o ajuste pela raiz. */
            while (2 * raiz + 1 < fim) { /* Usa somente a região ativa do heap. */
                int maior = 2 * raiz + 1; /* Calcula o filho esquerdo. */
                int direito = maior + 1; /* Calcula o filho direito. */

                m->comparacoes++; /* Compara os dois filhos candidatos. */
                if (direito < fim && v[direito] > v[maior]) { /* Verifica se o direito é maior. */
                    maior = direito; /* Seleciona o filho direito. */
                }
                m->comparacoes++; /* Compara a raiz com o maior filho. */
                if (v[raiz] >= v[maior]) { /* A propriedade de max-heap foi restaurada. */
                    break; /* Encerra este ajuste. */
                }
                temporario = v[raiz]; /* Guarda a raiz durante a troca. */
                v[raiz] = v[maior]; /* Move o maior filho para cima. */
                v[maior] = temporario; /* Move a raiz para baixo. */
                m->trocas++; /* Conta a permuta efetiva. */
                raiz = maior; /* Continua descendo no heap. */
            }
        }
    }
}
