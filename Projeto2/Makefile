# Nome do executavel
TARGET = main

# Diretorios
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -I$(INC_DIR)

# Lista de arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Lista de arquivos objeto
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# Regra principal
$(BIN_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para compilar os arquivos objeto
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Limpeza dos arquivos compilados
.PHONY: clean
clean:
	rm -rf $(BIN_DIR)/*.o $(BIN_DIR)/$(TARGET)

# Regras auxiliares
.PHONY: all
all: $(BIN_DIR)/$(TARGET)

.PHONY: test
testNumber: all
	clear
	./$(BIN_DIR)/$(TARGET) -s 100

testFile: all
	clear
	./$(BIN_DIR)/$(TARGET) -f dataset/sorteios.csv
