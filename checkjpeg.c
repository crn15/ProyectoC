#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <jpeglib.h>

// Verificar si un archivo es un JPEG
int ItsJPEG(const char *archivo) {
FILE *file = fopen(archivo, "rb");

if (file == NULL) {
fprintf(stderr, "No se pudo abrir el archivo\n");
return -1;
}

// Comprobar si los primeros tres bytes coinciden con el formato JPEG
unsigned char header[4];
fread(header, sizeof(unsigned char), 4, file);

if (header[0] == 0xFF && header[1] == 0xD8 && header[2] == 0xFF && header[3] == 0xE0) {
fclose(file);
return 1; // Es un archivo JPEG
} else {
fclose(file);
return 0; // No es un archivo JPEG
}
}

//Se lee el archivo JPEG y se prepara para ser manipulado
void ReadJPEG(const char *archivo) {
struct jpeg_decompress_struct cinfo;
struct jpeg_error_mgr jerr;

FILE *infile = fopen(archivo, "rb");
if (!infile) {
fprintf(stderr, "No se pudo abrir el archivo\n");
return;
}

cinfo.err = jpeg_std_error(&jerr);
jpeg_create_decompress(&cinfo);
jpeg_stdio_src(&cinfo, infile);
jpeg_read_header(&cinfo, TRUE);
jpeg_start_decompress(&cinfo);

int width = cinfo.output_width;
int height = cinfo.output_height;
int num_components = cinfo.output_components;

// Aquí se puede manipular la imagen

jpeg_finish_decompress(&cinfo);
jpeg_destroy_decompress(&cinfo);
fclose(infile);
}


int main() {
const char *archivo = "imagen.jpg";

int resultado = ItsJPEG(archivo);
if (resultado == 1) {
printf("%s es un archivo JPEG.\n", archivo);
ReadJPEG(archivo);
} else if (resultado == 0) {
printf("%s no es un archivo JPEG.\n", archivo);
} else {
fprintf(stderr, "Error al verificar el archivo.\n");
}

return 0;
}

