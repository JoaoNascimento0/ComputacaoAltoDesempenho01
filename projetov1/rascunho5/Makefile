CC = gcc
CFLAGS = -O0 -g
LIBS = -lm
SRCS = array.c metodo.c main.c
OBJ = main.o metodo.o array.o
TARGET = teste00

# Regra principal para compilar o programa
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(LIBS)

# Regras para os arquivos objeto
main.o: main.c metodo.h array.h
	$(CC) $(CFLAGS) -c main.c

metodo.o: metodo.c metodo.h
	$(CC) $(CFLAGS) -c metodo.c

array.o: array.c array.h
	$(CC) $(CFLAGS) -c array.c

# Regra de limpeza
clean:
	@rm -f $(OBJ) $(TARGET)

