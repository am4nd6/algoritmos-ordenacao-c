# Análise das métricas — versão inicial

Este arquivo registra a convenção usada nas implementações básicas atuais. A análise experimental completa será preenchida depois da execução do benchmark real.

## Selection Sort

- `comparacoes`: uma unidade para cada comparação entre `v[j]` e `v[menor]`.
- `trocas`: uma unidade para cada permuta efetiva; não há troca quando o menor já está na posição correta.
- Na implementação clássica, as comparações são `n(n-1)/2`.

## Insertion Sort

- `comparacoes`: uma unidade cada vez que `v[j]` é comparado com `chave`, inclusive a comparação falsa que encerra o deslocamento.
- `trocas`: representa movimentações; cada deslocamento de um elemento e a cópia da chave para sua posição final contam uma unidade.
- Entrada crescente tende ao melhor caso porque quase não desloca elementos.

## Merge Sort

- `comparacoes`: uma unidade para cada comparação entre os valores candidatos das duas metades.
- `trocas`: uma unidade para cada cópia para o buffer auxiliar e para cada cópia de retorno ao vetor original.
- O algoritmo usa memória auxiliar `O(n)` e tempo `O(n log n)`.

## Quick Sort

- O pivô é escolhido no elemento central do intervalo, evitando a regra proibida de sempre usar o primeiro ou o último elemento.
- `comparacoes`: conta as comparações dos valores com o pivô durante a procura dos índices.
- `trocas`: conta apenas permutas entre posições diferentes.
- O caso médio esperado é `O(n log n)` e o pior caso pode ser `O(n²)`, dependendo da distribuição e das partições.

## Heap Sort

- A estrutura é um max-heap armazenado no próprio vetor.
- Para um índice `i`, os filhos são `2*i+1` e `2*i+2`; a região ativa diminui após cada extração.
- O algoritmo usa memória auxiliar `O(1)` e tempo `O(n log n)`.

Esta convenção deverá ser mantida ao comparar os algoritmos e explicada novamente na análise final dos resultados.

## Benchmark realizado

O benchmark foi executado com `make bench`, usando GCC com `-O2`, `srand(42)`, três tipos de entrada, cinco repetições e medição somente da chamada de ordenação. O arquivo [`resultados.csv`](resultados.csv) possui 82 linhas: um cabeçalho e 81 combinações.

### Resumo de medições reais

Os valores abaixo foram extraídos do CSV produzido nesta execução. `tempo_ms` é a média das cinco repetições.

| Algoritmo | Tipo | n | tempo_ms | comparacoes | trocas |
|---|---|---:|---:|---:|---:|
| Bubble | aleatorio | 10000 | 232,537 | 49.995.000 | 25.230.454 |
| Bubble | aleatorio | 50000 | 6727,026 | 1.249.975.000 | 624.341.786 |
| Selection | aleatorio | 10000 | 115,616 | 49.995.000 | 9.992 |
| Selection | aleatorio | 50000 | 3178,871 | 1.249.975.000 | 49.982 |
| Insertion | crescente | 10000 | 0,202 | 9.999 | 9.999 |
| Insertion | crescente | 50000 | 0,178 | 49.999 | 49.999 |
| Insertion | decrescente | 10000 | 60,124 | 49.995.000 | 50.004.999 |
| Insertion | decrescente | 50000 | 1175,387 | 1.249.975.000 | 1.250.024.999 |
| Merge | aleatorio | 10000 | 0,653 | 120.387 | 267.232 |
| Merge | aleatorio | 50000 | 4,938 | 718.365 | 1.568.928 |
| Quick | aleatorio | 10000 | 0,623 | 178.484 | 30.989 |
| Quick | aleatorio | 50000 | 4,445 | 1.072.899 | 181.943 |
| Heap | aleatorio | 10000 | 1,202 | 235.392 | 124.192 |
| Heap | aleatorio | 50000 | 4,259 | 1.409.946 | 737.423 |

### Interpretação

- Os algoritmos quadráticos apresentaram crescimento forte de 10.000 para 50.000 elementos. Bubble aleatório passou de 232,537 ms para 6727,026 ms; Selection passou de 115,616 ms para 3178,871 ms.
- Insertion foi especialmente favorável na entrada crescente: os tempos ficaram próximos de zero e houve somente `n-1` comparações. Na entrada decrescente, o custo cresceu para a classe quadrática esperada.
- Selection manteve exatamente `n(n-1)/2` comparações e realizou poucas trocas, enquanto Bubble realizou muitas permutas, especialmente na entrada decrescente.
- Merge, Quick e Heap foram muito mais rápidos nos tamanhos maiores por apresentarem comportamento compatível com `O(n log n)` nesta experiência. Quick e Merge ficaram próximos na entrada aleatória; Heap teve mais movimentações.
- Quick utiliza pivô central. Isso ajuda nas entradas crescente e decrescente observadas, mas não elimina o pior caso teórico `O(n²)`.
- Os tempos não são leis matemáticas: cache, branches, alocação, otimização, sistema operacional e resolução do relógio influenciam a medição.

### Reprodutibilidade

O CSV foi produzido com:

```bash
make clean
make bench
wc -l docs/resultados.csv
```

O resultado foi `82` linhas físicas. Os algoritmos básicos não possuem linhas com `n=500000`; esse tamanho foi usado somente por Merge, Quick e Heap. A medição foi feita após restaurar a compilação normal, sem instrumentação de gcov ou gprof.

### Ambiente e condições

- Sistema: Ubuntu 24.04 no WSL 2, executado em Windows.
- CPU: Intel(R) Core(TM) i3-10105 CPU @ 3.70GHz, 8 CPUs lógicas.
- Compilador: GCC 15.2.0 (`gcc (Ubuntu 15.2.0-16ubuntu1)`).
- Build: GNU Make 4.4.1.
- Flags do benchmark: `-std=c11 -Wall -Wextra -O2 -MMD -MP -Isrc`.
- Data da execução: 23/11/2026.
- Condições: `srand(42)`, cinco repetições por combinação, entrada gerada uma vez e copiada antes de cada repetição, `clock()` somente na ordenação e saída validada antes de ser registrada.
