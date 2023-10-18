SOURCE_DIR = src
OBJ_DIR = ~/ProyectoC/ProyectoC/obj
BIN_DIR = ~/ProyectoC/ProyectoC/bin
HEADER_DIR = header/declaraciones.h
SRC_ARCHIVE = $(wildcard $(SOURCE_DIR)/*.c)

# Pasar objetos de al directorio donde estan los object files
OBJECT_FILES = $(patsubst $(SOURCE_DIR)/%.c, $(OBJ_DIR)/%.o , $(SRC_ARCHIVE))

OBJECTS = file_exist.c main_prueba1.c Png_Check2.c Png_Writer.c Entrada_Linea_comandos.c Png_Reader.c Transformacion.c

HEADER_FILE = $(wildcard $(HEADER_DIR)/%.h)

PROGRAM = ~/ProyectoC/ProyectoC/bin/Rotar

LDFLAGS = -lpng16

CDFLAGS = -Wall -Iinclude 
%.o: %.c $(HEADER_DIR)
	gcc -g  $(CDFLAGS) -c -o $@ $< 
$(PROGRAM): $(OBJECTS) 
	gcc -g $(CDFLAGS)    -o $@ $^  $(LDFLAGS)

#$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c $(HEADER_DIR)
#	gcc $(CDFLAGS) -c $< -o $@

.PHONY: clean 
clean: 
	rm -rf $(OBJ_DIR) $(BIN_DIR)
.PHONY: run 

run:
	./$(PROGRAM)
