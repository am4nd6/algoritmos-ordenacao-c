# Análise estática com Cppcheck

## Ferramenta

- Versão: Cppcheck 2.19.0
- Linguagem analisada: C11
- Diretórios analisados: `src` e `tests`

## Comando executado

```bash
make cppcheck
```

O alvo executa:

```bash
cppcheck --enable=warning,style,performance,portability \
  --inline-suppr --suppress=missingIncludeSystem src tests \
  > docs/cppcheck_bruto.txt 2>&1
```

## Resultado

O comando foi executado com sucesso e analisou os nove arquivos C existentes. Não foram encontrados apontamentos de severidade `error`, `warning`, `style`, `performance` ou `portability`.

A saída bruta da ferramenta está em [`cppcheck_bruto.txt`](cppcheck_bruto.txt). O arquivo foi gerado pela execução real e deve ser versionado junto com este relatório.

## Observações

- `missingIncludeSystem` foi suprimido conforme o roteiro, pois se refere a cabeçalhos do sistema e não ao código do projeto.
- `--inline-suppr` foi habilitado para permitir supressões locais justificadas caso sejam necessárias no futuro.
- A ausência de apontamentos não substitui testes funcionais, cobertura ou revisão humana.
