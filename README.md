# Trabalho Prático — Algoritmos de Ordenação em C

Projeto acadêmico da disciplina de **Estruturas de Dados — Terceira Unidade**. O objetivo é implementar, testar e comparar seis algoritmos clássicos de ordenação de inteiros em C11.

## Equipe

- **Amanda M. S.** — integrante 1 e responsável pelo desenvolvimento.
- **Eduarda Sousa Coelho** — integrante 2 e responsável pela defesa do vídeo.

## Objetivo

Dado um vetor de inteiros, reorganizar seus elementos em **ordem não decrescente**, sem criar, remover ou perder valores.

```text
Entrada: [8, 3, 3, -1]
Saída:   [-1, 3, 3, 8]
```

O projeto é composto por programas de terminal em C, não por uma aplicação web, API ou interface gráfica.

## Algoritmos

| Algoritmo | Arquivo | Estratégia | Complexidade esperada |
|---|---|---|---|
| Bubble Sort | `src/basicos/bubble.c` | Troca vizinhos fora de ordem | Geralmente `O(n²)` |
| Selection Sort | `src/basicos/selection.c` | Seleciona o menor restante | `O(n²)` |
| Insertion Sort | `src/basicos/insertion.c` | Insere a chave no prefixo ordenado | `O(n²)`; melhor `O(n)` |
| Merge Sort | `src/avancados/merge.c` | Divide e intercala | `O(n log n)` |
| Quick Sort | `src/avancados/quick.c` | Particiona ao redor de um pivô | Médio `O(n log n)`, pior `O(n²)` |
| Heap Sort | `src/avancados/heap.c` | Usa max-heap e extração | `O(n log n)` |

### Assinaturas obrigatórias

```c
void bubbleSort(int v[], int n, Metricas *m);
void selectionSort(int v[], int n, Metricas *m);
void insertionSort(int v[], int n, Metricas *m);
void mergeSort(int v[], int n, Metricas *m);
void quickSort(int v[], int n, Metricas *m);
void heapSort(int v[], int n, Metricas *m);
```

## Métricas

```c
typedef struct {
    unsigned long comparacoes;
    unsigned long trocas;
} Metricas;
```

`comparacoes` conta apenas comparações entre valores que decidem a ordem. `trocas` representa permutas efetivas em Bubble, Selection, Quick e Heap; em Insertion e Merge representa movimentações/cópias conforme uma convenção documentada.

Cada chamada deve começar com os contadores zerados. Os testes deverão validar ordenação e preservação de duplicatas, negativos e demais valores.

## Tecnologias e ambiente

- C11;
- Ubuntu via WSL2;
- GCC 15.2.0;
- GNU Make 4.4.1;
- gcov 15.2.0;
- gprof 2.46;
- cppcheck 2.19.0;
- Git/GitHub.


## Estrutura do projeto

```text
algoritmos-ordenacao-c/
├── README.md
├── Makefile
├── .gitignore
├── src/
│   ├── metricas.h
│   ├── algoritmos.h
│   ├── main.c
│   ├── bench.c
│   ├── basicos/{bubble,selection,insertion}.c
│   └── avancados/{merge,quick,heap}.c
├── tests/test_basic.c


```

## Instalação

No Ubuntu/WSL:

```bash
sudo apt update
sudo apt install git build-essential cppcheck
```

Verifique as ferramentas:

```bash
git --version
gcc --version
make --version
gcov --version
gprof --version
cppcheck --version
```

Entre no projeto:

```bash
cd /mnt/c/Users/caema80117.CAEMAPDC/Documents/GitHub/algoritmos-ordenacao-c
```

## Compilação atual

```bash
make clean
make
```

O comando gera `sort_main` usando C11, `-Wall`, `-Wextra`, `-O2`, `-MMD` e `-MP`. A estrutura atual foi compilada sem erros ou warnings.

## Execução atual

```bash
./sort_main <n> [bubble|selection|insertion|merge|quick|heap]
```

Exemplo:

```bash
./sort_main 10 bubble
```

Saída atual:

```text
Bubble Sort
  Tempo        : 0.001 ms
  Comparações  : 0
  Trocas       : 0
```

Esse zero é esperado enquanto as implementações não estão concluídas e não comprova a correção do algoritmo. A CLI deverá gerar dados com `srand(42)`, medir `clock()` e imprimir tempo, comparações e trocas.

## Alvos do Makefile

| Comando | Situação | Finalidade |
|---|---|---|
| `make` | Disponível | Compilar `sort_main` |
| `make clean` | Disponível | Remover objetos, dependências e binário |
| `make test` | Disponível, testes provisórios | Compilar e executar `test_basic` |
| `make coverage` | Preparado, relatório pendente | Gerar cobertura com gcov |
| `make cppcheck` | Disponível | Executar análise estática |
| `make profile` | Preparado, relatório pendente | Gerar perfil com gprof usando `-O0 -pg` |
| `make bench` | Disponível, benchmark pendente | Preparar `bench_sort` |

O benchmark não deve ser executado automaticamente por `make`, pois exige medição controlada.

## Testes e qualidade

`tests/test_basic.c` existe como ponto inicial, mas os testes reais ainda serão implementados. A suíte final deverá ter pelo menos dois casos para cada algoritmo, imprimir `PASSOU` ou `FALHOU`, retornar código diferente de zero quando houver falha, verificar ordenação e preservação do multiconjunto e cobrir entradas vazias, unitárias, ordenadas, invertidas, repetidas, negativas e aleatórias.

O cppcheck foi executado sobre `src` e `tests` na estrutura inicial, sem apontamentos. Isso não substitui a análise final após a implementação.

## Benchmark planejado

O arquivo final será `docs/resultados.csv`, com o cabeçalho:

```csv
algoritmo,tipo,n,tempo_ms,comparacoes,trocas
```

O protocolo exigirá seis algoritmos, três tipos de entrada (`aleatorio`, `crescente`, `decrescente`), tamanhos 1.000, 5.000, 10.000 e 50.000 para todos, e 500.000 somente para Merge, Quick e Heap. Cada combinação terá cinco repetições.

Isso produz 81 combinações, 405 ordenações medidas e 82 linhas físicas no CSV. Geração, cópia dos vetores e escrita do CSV ficarão fora da medição de tempo. O arquivo só será criado com dados de execução real.

## Uso de IA e autoria

A IA é usada como apoio didático, revisão e explicação. 

## Referências

- [Especificação oficial](https://lambdageo-edu.github.io/book-estrutura-de-dados/laboratorios/02_trabalho_pratico_ordenacao/)
- [Ordenação básica](https://lambdageo-edu.github.io/book-estrutura-de-dados/aulas/12_ordenacao_basica/)
- [Ordenação avançada](https://lambdageo-edu.github.io/book-estrutura-de-dados/aulas/13_ordenacao_avancada/)
- [Análise experimental](https://lambdageo-edu.github.io/book-estrutura-de-dados/aulas/14_analise_experimental/)
