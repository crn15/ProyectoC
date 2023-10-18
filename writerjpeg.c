#include <stdlib.h>
#include <stdio.h>
#include <jpeglib.h>
#include <jerror.h>

extern int width;
extern int height;
extern int numChannels;

int writeJPEGImage(const char *filename, unsigned char *newimageData, int width, int height, int numChannels) {
struct jpeg_compress_struct cinfo;
struct jpeg_error_mgr jerr;
FILE *outfile = NULL;

// Inicializa la estructura de manejo de errores.
cinfo.err = jpeg_std_error(&jerr);

// Inicializa la estructura de compresión.
jpeg_create_compress(&cinfo);

// Abre el archivo de salida en modo escritura binaria.
if ((outfile = fopen(filename, "wb")) == NULL) {
fprintf(stderr, "No se pudo abrir el archivo de salida %s\n", filename);

if (outfile != NULL) {
fclose(outfile); // Cierra el archivo si se abrió antes del error.
}
// Libera la estructura de compresión.
jpeg_destroy_compress(&cinfo);
return 0; // Error
}

// Configura el archivo de salida para JPEG.
jpeg_stdio_dest(&cinfo, outfile);

// Configura caracteristicas de la imagen.
cinfo.image_width = width;
cinfo.image_height = height;
cinfo.input_components = numChannels;
cinfo.in_color_space = JCS_RGB; // Espacio de color RGB.

// Configura los valores por defecto para la compresión JPEG.
jpeg_set_defaults(&cinfo);

// Inicia el proceso de compresión.
jpeg_start_compress(&cinfo, TRUE);

JSAMPROW row_pointer[1];
int row_stride = width * numChannels;

// Itera a través de las líneas de escaneo de la imagen y escribe cada línea.
while (cinfo.next_scanline < cinfo.image_height) {
row_pointer[0] = &newimageData[cinfo.next_scanline * row_stride];
if (jpeg_write_scanlines(&cinfo, row_pointer, 1) != 1) {
fprintf(stderr, "Error al escribir líneas de escaneo\n");

//Cierra el archivo en caso de error.
fclose(outfile);

// Libera la estructura de compresión.
jpeg_destroy_compress(&cinfo);
return 0; // Error
}
}

// Finaliza el proceso de compresión.
jpeg_finish_compress(&cinfo);

// Cierra el archivo de salida.
if (fclose(outfile) == EOF) {
fprintf(stderr, "Error al cerrar el archivo de salida\n");

//Libera la estructura de compresiòn.
jpeg_destroy_compress(&cinfo);
return 0; // Error
}

// Libera la estructura de compresión.
jpeg_destroy_compress(&cinfo);

return 1; // Éxito
}
