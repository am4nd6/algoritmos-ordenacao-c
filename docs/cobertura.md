# Cobertura de testes com gcov

## Comando

```bash
make coverage
```

O alvo recompila com `--coverage -g -O0`, executa `make test` e gera os relatórios individuais em `docs/gcov/`.

## Resultado real

| Arquivo | Linhas executáveis | Linhas executadas | Cobertura |
|---|---:|---:|---:|
| `bubble.c` | 11 | 11 | 100,00% |
| `selection.c` | 13 | 13 | 100,00% |
| `insertion.c` | 14 | 14 | 100,00% |
| `merge.c` | 42 | 41 | 97,62% |
| `quick.c` | 32 | 32 | 100,00% |
| `heap.c` | 39 | 39 | 100,00% |
| **Total agregado** | **151** | **150** | **99,34%** |

Fórmula usada:

```text
(150 / 151) × 100 = 99,34%
```

O cálculo é agregado: soma-se o número de linhas executadas dos seis algoritmos e divide-se pela soma de suas linhas executáveis. `main.c`, `bench.c` e `test_basic.c` não entram no denominador.

## Artefatos

- `docs/gcov/resumo.txt` contém a saída real do gcov.
- `docs/gcov/bubble.c.gcov`
- `docs/gcov/selection.c.gcov`
- `docs/gcov/insertion.c.gcov`
- `docs/gcov/merge.c.gcov`
- `docs/gcov/quick.c.gcov`
- `docs/gcov/heap.c.gcov`

## Interpretação e limitações

A cobertura agregada de 99,34% supera o mínimo exigido de 70%. Uma linha de `merge.c` não foi executada pelos cenários atuais, mas isso não significa que cobertura alta prove a correção completa. Os resultados devem continuar sendo complementados por testes funcionais, revisão de limites, análise de memória e validação das métricas.
