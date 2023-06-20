# DIRETORIOS
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
BIN_DIR = bin
TST_DIR = $(SRC_DIR)/tests
LIB_DIR = $(INC_DIR)/lib

# NOME DOS EXECUTAVEIS
PROGRAM_NAME = program
TEST_NAME = test

# CONFIGURAÇÕES DO COMPILADOR
OS_NAME := $(shell grep -oP '(?<=^NAME=).+' /etc/os-release | tr -d '"')

ifeq ($(OS_NAME), Ubuntu)
    # Please, install g++12: sudo apt install g++-12
	CC = g++-12

else
	CC = g++

endif

LIBS = -lm
CFLAGS = --std=c++20 -O0 -Wall

# ARQUIVOS
MAIN = $(OBJ_DIR)/main.o

PROGRAM_OBJS =	$(OBJ_DIR)/list_doubly_linked.o \
				$(OBJ_DIR)/list_excpt.o \
				$(OBJ_DIR)/queue.o \
				$(OBJ_DIR)/queue_excpt.o \
				$(OBJ_DIR)/vector.o \
				$(OBJ_DIR)/vector_excpt.o \
				$(OBJ_DIR)/stack.o \
				$(OBJ_DIR)/stack_excpt.o \
				$(OBJ_DIR)/queue_singly_linked.o \
				$(OBJ_DIR)/stack_singly_linked.o \
				$(OBJ_DIR)/binary_tree.o \
				$(OBJ_DIR)/utils.o \
				$(OBJ_DIR)/node_doubly_linked.o \
				$(OBJ_DIR)/node_singly_linked.o

TEST_OBJS = $(OBJ_DIR)/list_doubly_linked_test.o \
			$(OBJ_DIR)/queue_singly_linked_test.o \
			$(OBJ_DIR)/stack_singly_linked_test.o \
			$(OBJ_DIR)/stack_test.o \
			$(OBJ_DIR)/queue_test.o \
			$(OBJ_DIR)/vector_test.o \
			$(OBJ_DIR)/main_doctest.o

# CASES
build: $(OBJ_DIR)/$(PROGRAM_NAME)

run: build
	$(BIN_DIR)/$(PROGRAM_NAME)

tests: $(OBJ_DIR)/$(TEST_NAME)
	$(BIN_DIR)/$(TEST_NAME)

$(OBJ_DIR)/$(TEST_NAME): $(TEST_OBJS) $(PROGRAM_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(PROGRAM_OBJS) -o $(BIN_DIR)/$(TEST_NAME)

$(OBJ_DIR)/$(PROGRAM_NAME): $(PROGRAM_OBJS) $(MAIN)
	$(CC) $(CFLAGS) $(PROGRAM_OBJS) $(MAIN) -o $(BIN_DIR)/$(PROGRAM_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(INC_DIR)/%.hh
	$(CC) -c $(CFLAGS) $< -I $(INC_DIR) -o $@

$(OBJ_DIR)/%.o: $(TST_DIR)/%.cc
	$(CC) -c $(CFLAGS) $< -I $(INC_DIR) -I $(LIB_DIR) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CC) -c $(CFLAGS) $< -I $(INC_DIR) -o $@

valgrind: tests build
	valgrind --leak-check=full $(BIN_DIR)/$(TEST_NAME) > /dev/null
	valgrind --leak-check=full $(BIN_DIR)/$(PROGRAM_NAME)

clean:
	rm -f $(BIN_DIR)/* $(OBJ_DIR)/* gmon.out
