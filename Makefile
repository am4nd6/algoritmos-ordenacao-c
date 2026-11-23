# Compilador usado para transformar C em código executável.
CC = gcc
# Opções: C11, avisos, otimização e arquivos automáticos de dependência.
CFLAGS = -std=c11 -Wall -Wextra -O2 -MMD -MP
# Informa onde ficam os cabeçalhos do projeto.
CPPFLAGS = -Isrc

# Lista os seis arquivos que futuramente conterão os algoritmos.
ALGORITMOS = src/basicos/bubble.c src/basicos/selection.c src/basicos/insertion.c \
             src/avancados/merge.c src/avancados/quick.c src/avancados/heap.c
OBJETOS = $(ALGORITMOS:.c=.o)
MAIN_OBJ = src/main.o

# Diz que estes nomes são comandos, não arquivos reais.
.PHONY: all clean test bench cppcheck coverage profile

# O comando padrão gera o programa principal.
all: sort_main

# Junta os arquivos compilados e cria o executável.
sort_main: $(MAIN_OBJ) $(OBJETOS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^

# Regra geral: transforma cada arquivo .c em um arquivo .o.
%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# Inclui dependências geradas automaticamente, se existirem.
-include $(MAIN_OBJ:.o=.d) $(OBJETOS:.o=.d)

# Remove binários e arquivos intermediários da compilação.
clean:
	rm -f sort_main $(MAIN_OBJ) $(OBJETOS) $(MAIN_OBJ:.o=.d) $(OBJETOS:.o=.d)

# Compila e executa o ponto inicial da suíte de testes.
test_basic: tests/test_basic.c src/basicos/bubble.o src/basicos/selection.o src/basicos/insertion.o src/avancados/merge.o src/avancados/quick.o src/avancados/heap.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^

# Executa os testes automatizados disponíveis.
test: test_basic
	./test_basic

# Compila o ponto inicial do benchmark.
bench_sort: src/bench.c $(OBJETOS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^

# Prepara a execução futura do benchmark.
bench: bench_sort
	@echo "Benchmark real pendente das implementacoes dos algoritmos."

# Executa a análise estática dos fontes existentes.
cppcheck:
	cppcheck --enable=warning,style,performance,portability --inline-suppr --suppress=missingIncludeSystem src tests > docs/cppcheck_bruto.txt 2>&1

# Estes alvos serão completados quando houver testes e implementações reais.
coverage:
	mkdir -p docs/gcov
	rm -f docs/gcov/*.gcov docs/gcov/resumo.txt
	$(MAKE) clean
	$(MAKE) CFLAGS="-std=c11 -Wall -Wextra --coverage -g -O0 -MMD -MP" test
	for arquivo in src/basicos/bubble.c src/basicos/selection.c src/basicos/insertion.c src/avancados/merge.c src/avancados/quick.c src/avancados/heap.c; do gcov -o "$$(dirname "$$arquivo")" "$$arquivo"; done > docs/gcov/resumo.txt 2>&1
	mv ./*.c.gcov docs/gcov/ 2>/dev/null || true
	@echo "Relatorios gcov gerados em docs/gcov."

N ?= 50000
ALG ?= quick

# Compila uma versão separada, sem otimização, para o gprof.
sort_profile: src/main.c $(ALGORITMOS)
	$(CC) -std=c11 -Wall -Wextra -O0 -g -pg $(CPPFLAGS) -o $@ $^

# Executa uma carga controlada e salva o perfil bruto.
profile: sort_profile
	rm -f gmon.out docs/perfil_bruto.txt
	./sort_profile $(N) $(ALG) > /dev/null
	gprof sort_profile gmon.out > docs/perfil_bruto.txt
	@echo "Perfil salvo em docs/perfil_bruto.txt (N=$(N), ALG=$(ALG))."
