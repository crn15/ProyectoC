#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <jpeglib.h>
#include "declaraciones.h"
// Verificar si un archivo es un JPEG
int ItsJPEG(const char *archivo) {
	FILE *file = fopen(archivo, "rb");

	if (file == NULL) {
		fprintf(stderr, "No se pudo abrir el archivo\n");
		return False;
	}

// Comprobar si los primeros tres bytes coinciden con el formato JPEG
	unsigned char header[4];
	fread(header, sizeof(unsigned char), 4, file);

	if (header[0] == 0xFF && header[1] == 0xD8 && header[2] == 0xFF && header[3] == 0xE0) {
		fclose(file);
		return True; // Es un archivo JPEG
	} else {
		fclose(file);
		return False; // No es un archivo JPEG
	}
}

