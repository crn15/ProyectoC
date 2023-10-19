SOURCE_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
HEADER_DIR = header/declaraciones.h
SRC_ARCHIVE = $(wildcard $(SOURCE_DIR)/*.c)
CC = gcc
# Pasar objetos de al directorio donde estan los object files
OBJECT_FILES = $(patsubst $(SOURCE_DIR)/%.c, $(OBJ_DIR)/%.o , $(SRC_ARCHIVE))




PROGRAM = $(BIN_DIR)/Rotar

LDFLAGS = -lpng16

CDFLAGS = -Wall -Iinclude
#EXP = scr/Entrada_Linea_comandos.c
#%.o: %.c $(HEADER_DIR)
#	gcc -c -o $@  $< $(CDFLAGS)

$(PROGRAM): $(OBJECT_FILES)
	$(CC) $(CDFLAGS)    -o $@ $^  $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c 
	$(CC) $(CDFLAGS) -c $< -o $@

.PHONY: clean 
clean: 
	rm -rf $(OBJ_DIR) $(BIN_DIR)
.PHONY: run 

run: $(PROGRAM)
	./$(PROGRAM)


$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))
