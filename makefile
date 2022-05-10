OBJ_DIR := obj
BIN_DIR := bin
SRC_DIR := src
LIST_DIR := list

all: clean task1b # task2b task1b

task1b: $(OBJ_DIR)/start.o $(OBJ_DIR)/util.o $(OBJ_DIR)/task1b.o
	ld -m elf_i386 $(OBJ_DIR)/start.o $(OBJ_DIR)/task1b.o $(OBJ_DIR)/util.o -o $(BIN_DIR)/task1b

task2b: $(OBJ_DIR)/start.o $(OBJ_DIR)/util.o $(OBJ_DIR)/task2b.o
	ld -m elf_i386 $(OBJ_DIR)/start.o $(OBJ_DIR)/task2b.o $(OBJ_DIR)/util.o -o $(BIN_DIR)/task2b

task2c: $(OBJ_DIR)/start.o $(OBJ_DIR)/util.o $(OBJ_DIR)/task2c.o
	ld -m elf_i386 $(OBJ_DIR)/start.o $(OBJ_DIR)/task2c.o $(OBJ_DIR)/util.o -o $(BIN_DIR)/task2c

$(OBJ_DIR)/start.o: $(SRC_DIR)/start.s
	nasm -f elf32 $(SRC_DIR)/start.s -o $(OBJ_DIR)/start.o

$(OBJ_DIR)/util.o: $(SRC_DIR)/util.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector $(SRC_DIR)/util.c -o $(OBJ_DIR)/util.o

$(OBJ_DIR)/task1b.o: $(SRC_DIR)/task1b.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector $(SRC_DIR)/task1b.c -o $(OBJ_DIR)/task1b.o

$(OBJ_DIR)/task2b.o: $(SRC_DIR)/task2b.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector $(SRC_DIR)/task2b.c -o $(OBJ_DIR)/task2b.o

$(OBJ_DIR)/task2c.o: $(SRC_DIR)/task2c.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector $(SRC_DIR)/task2c.c -o $(OBJ_DIR)/task2c.o


clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/* $(LIST_DIR)/*
