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
test_basic: tests/test_basic.c src/basicos/bubble.o
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
	cppcheck --enable=warning,style,performance,portability --suppress=missingIncludeSystem src tests

# Estes alvos serão completados quando houver testes e implementações reais.
coverage:
	@echo "Cobertura gcov pendente das implementacoes e testes reais."

profile:
	@echo "Profiling gprof pendente das implementacoes reais."
