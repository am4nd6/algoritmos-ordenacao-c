# Como rodar o projeto

Guia para instalar o ambiente, baixar o projeto, compilar, executar os algoritmos, testar e gerar os relatórios. Os comandos são para Ubuntu/WSL, salvo indicação contrária.

## 1. Instalar Ubuntu no Windows

Abra o PowerShell como administrador e execute:

    wsl --install

Reinicie se solicitado. Depois confira:

    wsl --status
    wsl --list --verbose

Deve existir Ubuntu com versão 2. Se necessário, use `wsl --install -d Ubuntu`. Abra Ubuntu pelo menu Iniciar e crie usuário e senha Linux. A senha não aparece durante a digitação; isso é normal.

## 2. Instalar ferramentas

No Ubuntu, execute:

    sudo apt update
    sudo apt install -y git build-essential cppcheck

`build-essential` instala GCC e Make. Confira as ferramentas:

    git --version
    gcc --version
    make --version
    gcov --version
    gprof --version
    cppcheck --version

Cada comando deve mostrar uma versão. `command not found` significa que a ferramenta precisa ser instalada.

## 3. Clonar com Git

O repositório deste projeto é `https://github.com/am4nd6/algoritmos-ordenacao-c.git`. Clone-o com:

    mkdir -p ~/projetos
    cd ~/projetos
    git clone https://github.com/am4nd6/algoritmos-ordenacao-c.git
    cd algoritmos-ordenacao-c

Com SSH, se a chave pública já estiver cadastrada:

    git clone git@github.com:am4nd6/algoritmos-ordenacao-c.git
    cd algoritmos-ordenacao-c

Se o projeto estiver em uma pasta do Windows:

    cd /mnt/c/Users/SEU_USUARIO/Documents/GitHub/algoritmos-ordenacao-c

Confira:

    pwd
    ls
    git status

Devem aparecer `Makefile`, `README.md`, `src`, `tests` e `docs`.

## 4. Compilar e executar

Compile do zero:

    make clean
    make
    ls -l sort_main

`make clean` remove objetos antigos. `make` compila em C11 com `-Wall -Wextra -O2` e cria `sort_main`.

Execute os seis algoritmos:

    ./sort_main 10 bubble
    ./sort_main 10 selection
    ./sort_main 10 insertion
    ./sort_main 10 merge
    ./sort_main 10 quick
    ./sort_main 10 heap

Execute todos sobre cópias da mesma entrada:

    ./sort_main 10

Teste entradas inválidas:

    ./sort_main
    ./sort_main abc
    ./sort_main 10 algoritmo_inexistente

## 5. Testes automatizados

    make test
    echo $?

Cada caso deve imprimir `PASSOU`. O código `0` significa sucesso.

## 6. Cppcheck

    make cppcheck
    cat docs/cppcheck_bruto.txt
    less docs/cppcheck.md

O alvo analisa `src` e `tests`. Pressione `q` para sair do `less`.

## 7. Cobertura com gcov

    make coverage
    ls docs/gcov
    cat docs/gcov/resumo.txt
    less docs/cobertura.md

O alvo recompila com `--coverage -g -O0`, executa os testes e gera seis relatórios `.gcov`. Depois restaure a compilação normal:

    make clean
    make
    make test

Arquivos `.gcda` e `.gcno` são temporários; os relatórios em `docs/gcov/` são as evidências.

## 8. Profiling com gprof

O perfil padrão usa `N=50000` e `ALG=quick`:

    make profile

Ele usa `-O0 -g -pg`, cria `gmon.out` e atualiza `docs/perfil_bruto.txt`. Exemplos:

    make profile N=50000 ALG=merge
    make profile N=200000 ALG=quick
    grep -n "Flat profile" docs/perfil_bruto.txt
    grep -n "Call graph" docs/perfil_bruto.txt
    less docs/perfil.md

Profiling usa `-O0 -pg`; benchmark usa `-O2`. Os tempos não devem ser comparados diretamente.

## 9. Benchmark

    make clean
    make bench
    wc -l docs/resultados.csv
    head docs/resultados.csv
    tail docs/resultados.csv
    grep -E '^(bubble|selection|insertion),[^,]+,500000,' docs/resultados.csv
    less docs/analise.md

O esperado é `82 docs/resultados.csv`: cabeçalho e 81 combinações. O último `grep` não deve imprimir linhas, pois `500000` é reservado a Merge, Quick e Heap.

## 10. Sequência completa

    make clean
    make
    make test
    make cppcheck
    make coverage
    make clean
    make
    make test
    make profile
    make clean
    make bench
    wc -l docs/resultados.csv

O segundo `make clean` restaura as flags normais após a cobertura.

## 11. Atualizar o projeto com o commit mais recente

Antes de atualizar, entre na pasta do projeto e confira se há alterações locais:

    cd ~/projetos/algoritmos-ordenacao-c
    git status

Se não houver arquivos modificados, baixe as mudanças da branch principal:

    git pull origin main

`git pull` busca os commits mais recentes no GitHub e os incorpora à cópia local. Depois da atualização, confira novamente:

    git log --oneline -5
    git status

Se o projeto usar outra branch, descubra a branch atual com `git branch --show-current` e substitua `main` pelo nome correto.

### Se houver alterações locais

Não execute `git pull` sem entender o que acontecerá com alterações locais. Primeiro veja as diferenças:

    git diff

Se quiser manter as alterações temporariamente, guarde-as:

    git stash push -m "alteracoes locais antes de atualizar"
    git pull origin main
    git stash pop

Se as alterações já estiverem prontas e forem autoria sua, faça um commit antes de atualizar:

    git add caminho/do/arquivo
    git commit -m "tipo: descreve a alteracao"
    git pull origin main

### Se aparecer um conflito

O Git informará quais arquivos têm conflito. Abra esses arquivos, procure as marcas `<<<<<<<`, `=======` e `>>>>>>>`, escolha a versão correta e remova as marcas. Depois execute:

    git add arquivo-com-conflito
    git commit -m "fix: resolve conflito de atualizacao"

Se não souber resolver, não apague arquivos nem use comandos destrutivos. Pare e peça ajuda à dupla.

Depois de qualquer atualização, recompile e teste:

    make clean
    make
    make test

## 12. Limpeza e Git

    make clean
    rm -f test_basic bench_sort sort_profile gmon.out
    git status --short
    git diff
    git status --short --untracked-files=all

Não remova relatórios em `docs/`. Depois de revisar cuidadosamente, um integrante autorizado pode usar:

    git add README.md Makefile src tests docs .gitignore
    git status
    git commit -m "docs: adiciona guia completo de execucao"
    git push

Nunca adicione senhas, tokens ou chaves privadas.

## 13. Problemas comuns

Para `command not found`:

    sudo apt update
    sudo apt install -y git build-essential cppcheck

Para `sort_main` inexistente:

    pwd
    ls
    make
    ./sort_main 10 quick

Para CSV inexistente:

    make clean
    make bench
    ls -l docs/resultados.csv

Se os testes falharem depois da cobertura:

    make clean
    make
    make test

A senha do `sudo` não aparece durante a digitação. Ao final, devem existir o executável, testes aprovados, relatórios de cppcheck, gcov e gprof, `docs/resultados.csv` com 82 linhas e `docs/analise.md`.
