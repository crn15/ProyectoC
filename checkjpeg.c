#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <jerror.h>
#include "declarations.h"


// Función para cargar imagen JPEG.
ImageData loadJPEGImage(const char *filename) {
ImageData imageData;
imageData.data = NULL;
imageData.width = 0;
imageData.height = 0;
imageData.numChannels = 0;

struct jpeg_decompress_struct cinfo;
struct jpeg_error_mgr jerr;

// Abre imagen en modo lectura binaria.
FILE *infile = fopen(filename, "rb");
if (!infile) {
fprintf(stderr, "No se pudo abrir el archivo %s\n", filename);
return imageData;
}

cinfo.err = jpeg_std_error(&jerr);

// Inicia estructura de descompresion.
jpeg_create_decompress(&cinfo);
jpeg_stdio_src(&cinfo, infile);
jpeg_read_header(&cinfo, TRUE);
jpeg_start_decompress(&cinfo);

// Guarda caracteristicas de la imagen en ImageData.
imageData.width = cinfo.output_width;
imageData.height = cinfo.output_height;
imageData.numChannels = cinfo.output_components;

// Asigna memoria.
imageData.data = (unsigned char *)malloc(imageData.width * imageData.height * imageData.numChannels);

if (!imageData.data) {
fprintf(stderr, "Error al asignar memoria para los datos de la imagen\n");
fclose(infile);
jpeg_destroy_decompress(&cinfo);
return imageData;
}

// Lee lineas de la imagen y las guarda en imageData.data
JSAMPROW row_pointer[1];
while (cinfo.output_scanline < cinfo.output_height) {
row_pointer[0] = &imageData.data[(cinfo.output_scanline) * imageData.width * imageData.numChannels];
jpeg_read_scanlines(&cinfo, row_pointer, 1);
}

// Termina descompresiòn y libera recursos.
jpeg_finish_decompress(&cinfo);
jpeg_destroy_decompress(&cinfo);
fclose(infile);

return imageData; //Retorna datos de la imagen.
}

int main(int argc, char *argv[]) {
if (argc != 2) {
fprintf(stderr, "Uso: %s <nombre_de_archivo.jpeg>\n", argv[0]);
return 1;
}

const char *filename = argv[1];

//Llamada a funcion que carga la imagen.
ImageData imageData = loadJPEGImage(filename);

if (imageData.data != NULL) {

// Llamada a funcion que retorna matriz de píxeles.
unsigned char *pixelArray = JPEGMatrix(&imageData);

//Llamada a funcion que escribe la imagen.
writeJPEGImage("nueva_imagen.jpeg", pixelArray, imageData.width, imageData.height);

printf("Imagen rotada guardada como 'nueva_imagen.jpeg'\n");

// Libera la memoria de la matriz de píxeles.
free(pixelArray);

// Libera la memoria de los datos de la imagen.
free(imageData.data);
}

return 0;
}

