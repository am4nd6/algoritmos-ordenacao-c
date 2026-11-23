# Decisões técnicas — Fase 3

## Métricas

1. `comparacoes` contará apenas comparações entre valores do vetor que influenciam a ordem. Condições de laços, índices, ponteiros e alocação não serão contadas.
2. Bubble, Selection, Quick e Heap contarão uma troca para cada permuta efetiva entre duas posições.
3. Insertion e Merge usarão `trocas` como contador de movimentações/cópias. A implementação de cada algoritmo deverá documentar exatamente quais escritas serão contadas.
4. O chamador inicializará `Metricas` com zero antes de cada execução e fornecerá um ponteiro válido. A API pública não altera suas assinaturas para tratar ponteiro nulo.
5. Os valores dos contadores serão mantidos em `unsigned long`, conforme o contrato atual de `src/metricas.h`.

## CLI inicial

- O tamanho `n` deve ser inteiro positivo e caber em `int`.
- `srand(42)` é chamado uma vez para produzir entradas reproduzíveis.
- O vetor original é gerado uma vez e cada algoritmo recebe uma cópia independente.
- A cópia e a geração ficam fora da medição; somente a chamada de ordenação é cronometrada.
- Os stubs atuais ainda não alteram o vetor nem incrementam contadores. Isso é intencional e será substituído nas fases de implementação.

## Makefile

- A compilação usa C11, `-Wall`, `-Wextra`, `-O2`, `-MMD` e `-MP`.
- `make` gera `sort_main`; `make clean` remove artefatos intermediários.
- Os alvos de testes, benchmark, cobertura, profiling e cppcheck foram preparados, mas os relatórios finais dependem das implementações e testes das próximas fases.
