# Variáveis para compilação
CC = gcc
CFLAGS = -O0 -g -pg
LIBS = -lm

#para o programa main()
SRCS = array.c metodo.c main.c
OBJ = main.o metodo.o array.o
TARGET = teste00

#para o programa solucaoAnalitica()
SRCS2 = array.c solucaoAnalitica.c
OBJ2 = solucaoAnalitica.o array.o
TARGET2 = solucaoAnalitica

#compilar ambos os programas
all: $(TARGET) $(TARGET2)

# Regras para compilar main()
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(LIBS)

# Regras para compilar solucaoAnalitica()
$(TARGET2): $(OBJ2)
	$(CC) $(CFLAGS) $(OBJ2) -o $(TARGET2) $(LIBS)

# Regras para os arquivos objeto de main()
main.o: main.c metodo.h array.h
	@echo
	@echo "para executar main(): make run, para executar solucaoAnalitica(): make run_solucao."
	@echo

	$(CC) $(CFLAGS) -c main.c

metodo.o: metodo.c metodo.h
	$(CC) $(CFLAGS) -c metodo.c

array.o: array.c array.h
	$(CC) $(CFLAGS) -c array.c

# Regras para os arquivos objeto de solucaoAnalitica()
solucaoAnalitica.o: solucaoAnalitica.c array.h
	$(CC) $(CFLAGS) -c solucaoAnalitica.c

# Regra de limpeza
clean:
	@rm -f $(OBJ) $(TARGET)
	@rm -f $(OBJ2) $(TARGET2)
	@rm -f *.o

# Regra para rodar main()
run: $(TARGET)
	./$(TARGET)

# Regra para rodar solucaoAnalitica
run_solucao: $(TARGET2)
	./$(TARGET2)
