# Profiling com gprof

## Execução

- Ferramenta: GNU gprof 2.46.
- Compilação: GCC com `-O0 -g -pg`.
- Comando: `make profile`.
- Carga: `N=50000`, algoritmo `quick`.
- Entrada: vetor aleatório reproduzível com `srand(42)`.
- Relatório bruto: [`perfil_bruto.txt`](perfil_bruto.txt).

O alvo compila `sort_profile`, remove um `gmon.out` anterior, executa a carga e gera o relatório com `gprof sort_profile gmon.out`.

## Interpretação do perfil real

O relatório contém a seção `Flat profile` e o grafo de chamadas. A função dominante foi `particionar`, com:

- 100,00% do tempo amostrado;
- 0,01 segundos acumulados;
- 49.999 chamadas.

Isso é coerente com o Quick Sort: cada intervalo é particionado em torno do pivô central e a função recursiva `ordenar_intervalo` chama `particionar` repetidamente. O grafo registra 99.998 chamadas recursivas de `ordenar_intervalo` e uma chamada pública de `quickSort`.

## Limitações

- O tempo total foi muito pequeno e o relatório teve somente uma amostra de 0,01 segundo.
- Percentuais iguais a zero não significam custo exatamente zero; significam que não receberam amostras suficientes.
- O profiling foi compilado com `-O0 -pg`, enquanto o benchmark deverá usar `-O2`; portanto, os tempos não devem ser comparados diretamente.
- O gprof é amostral e não substitui testes, cobertura ou benchmark controlado.

## Relação com a complexidade

O número elevado de chamadas de particionamento é compatível com o trabalho recursivo do Quick Sort. A escolha do pivô central reduz padrões ruins em entradas ordenadas, mas não elimina a possibilidade teórica de pior caso `O(n²)`. O profiling observado descreve esta execução específica e não prova uma complexidade diferente da análise teórica.
