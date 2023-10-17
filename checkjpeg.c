#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

typedef struct {
unsigned char *data;
int width;
int height;
int numChannels;
} ImageData;

// Función para cargar una imagen JPEG con manejo de errores.
ImageData loadJPEGImage(const char *filename) {
ImageData imageData;
imageData.data = NULL;
imageData.width = 0;
imageData.height = 0;
imageData.numChannels = 0;

struct jpeg_decompress_struct cinfo;
struct jpeg_error_mgr jerr;

// Abre el archivo JPEG en modo lectura binaria.
FILE *infile = fopen(filename, "rb");
if (!infile) {
fprintf(stderr, "No se pudo abrir el archivo %s\n", filename);
return imageData; // Devuelve una estructura vacía si hay un error.
}

// Configura el manejador de errores para libjpeg.
cinfo.err = jpeg_std_error(&jerr);

// Crea la estructura de descompresión de JPEG.
jpeg_create_decompress(&cinfo);
jpeg_stdio_src(&cinfo, infile);
jpeg_read_header(&cinfo, TRUE);
jpeg_start_decompress(&cinfo);

// Obtiene información sobre la imagen.
imageData.width = cinfo.output_width;
imageData.height = cinfo.output_height;
imageData.numChannels = cinfo.output_components;

// Asigna memoria para los datos de la imagen.
imageData.data = (unsigned char *)malloc(imageData.width * imageData.height * imageData.numChannels);

// Manejo de errores en la asignación de memoria.
if (!imageData.data) {
fprintf(stderr, "Error al asignar memoria para los datos de la imagen\n");
fclose(infile);
jpeg_destroy_decompress(&cinfo);
return imageData;
}

// Lee y descomprime la imagen línea por línea.
JSAMPROW row_pointer[1];
while (cinfo.output_scanline < cinfo.output_height) {
row_pointer[0] = &imageData.data[(cinfo.output_scanline) * imageData.width * imageData.numChannels];
jpeg_read_scanlines(&cinfo, row_pointer, 1);
}

// Finaliza la descompresión y libera los recursos.
jpeg_finish_decompress(&cinfo);
jpeg_destroy_decompress(&cinfo);
fclose(infile);

return imageData;
}

int main(int argc, char *argv[]) {
if (argc != 2) {
fprintf(stderr, "Uso: %s <nombre_de_archivo.jpeg>\n", argv[0]);
return 1;
}

const char *filename = argv[1];

// Llama a la función para cargar la imagen JPEG.
ImageData imageData = loadJPEGImage(filename);

if (imageData.data) {
printf("Ancho de la imagen: %d\n", imageData.width);
printf("Alto de la imagen: %d\n", imageData.height);
printf("Número de componentes de color: %d\n", imageData.numChannels);

// Puedes acceder a los datos de la imagen en imageData.data y procesarlos aquí.
// No olvides liberar la memoria cuando hayas terminado.
free(imageData.data);
};

return 0;
}

