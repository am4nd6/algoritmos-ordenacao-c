# Fase 1 — Evidências do ambiente

**Data da verificação:** 23/11/2026

## Ambiente detectado

- WSL disponível: sim.
- Distribuição: Ubuntu.
- Versão do WSL: 2.
- Estado durante a verificação: `Running`.
- Distribuição padrão: Ubuntu.


## Ferramentas

| Ferramenta | Resultado |
|---|---|
| Git | Disponível — `git version 2.53.0` |
| GCC | Disponível — Ubuntu 15.2.0-16ubuntu1 |
| Make | Disponível — GNU Make 4.4.1 |
| gcov | Disponível — Ubuntu 15.2.0-16ubuntu1 |
| gprof | Disponível — GNU Binutils 2.46 |
| cppcheck | Disponível — Cppcheck 2.19.0 |

## Instalação realizada

Foi tentada a instalação com:

```bash
sudo apt-get update
sudo DEBIAN_FRONTEND=noninteractive apt-get install -y git build-essential cppcheck
```

A instalação foi concluída pelo usuário administrativo do Ubuntu/WSL porque o `sudo` exigiu autenticação interativa.

Também foram aprovados os testes de um programa mínimo com `gcc -std=c11 -Wall -Wextra`.

