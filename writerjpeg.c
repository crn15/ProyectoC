#include <stdlib.h>
#include <stdio.h>
#include <jpeglib.h>
#include <jerror.h>

// Función para obtener una matriz de píxeles de la imagen.
unsigned char* JPEGMatrix(const ImageData *imageData) {
unsigned char *pixelArray;
int imageSize = imageData->width * imageData->height * imageData->numChannels;

//Asigna memoria para la matriz.
pixelArray = (unsigned char *)malloc(imageSize * sizeof(unsigned char));

for (int i = 0; i < imageSize; i++) {
pixelArray[i] = imageData->data[i];
}

return pixelArray; //Retorna matriz de pixeles.
}

// Función para guardar una imagen JPEG.
void writeJPEGImage(const char *filename, const unsigned char *rotatedimage, int width, int height) {
struct jpeg_compress_struct cinfo;
struct jpeg_error_mgr jerr;

int numChannels=3;
int quality=95;

//Abre el archivo de salida en modo lectura binaria.
FILE *outfile = fopen(filename, "wb");
if (!outfile) {
fprintf(stderr, "No se pudo abrir el archivo de salida: %s\n", filename);
return;
}
cinfo.err = jpeg_std_error(&jerr);

//Inicia estructura de compresion.
jpeg_create_compress(&cinfo);
jpeg_stdio_dest(&cinfo, outfile);

//Configura caracteristicas de la imagen.
cinfo.image_width = width;
cinfo.image_height = height;
cinfo.input_components = numChannels;
cinfo.in_color_space = JCS_RGB;

jpeg_set_defaults(&cinfo);
jpeg_set_quality(&cinfo, quality, TRUE);

jpeg_start_compress(&cinfo, TRUE);

JSAMPROW row_pointer[1];
int row_stride = width * numChannels;

while (cinfo.next_scanline < cinfo.image_height) {
row_pointer[0] = (JSAMPROW)&rotatedimage[cinfo.next_scanline * row_stride];
jpeg_write_scanlines(&cinfo, row_pointer, 1);
}

//Termina compresion y se liberan recursos.
jpeg_finish_compress(&cinfo);
fclose(outfile);
jpeg_destroy_compress(&cinfo);
}

