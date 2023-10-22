#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <jerror.h>
#include "declaraciones.h"
int width_jpeg, height_jpeg;
// Función para cargar imagen JPEG.
int loadJPEGImage(const char *filename, JSAMPLE **filas_ptr) {
	//ImageData imageData;
	//imageData.data = NULL;
	//imageData.width = 0;
	//imageData.height = 0;
	//imageData.numChan
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	JSAMPARRAY buffer;
	int row_s;
	// Abre imagen en modo lectura binaria.
	FILE *infile = fopen(filename, "rb");
	if (!infile) {
		fprintf(stderr, "No se pudo abrir el archivo %s\n", filename);
		return False;
	}

	cinfo.err = jpeg_std_error(&jerr);
	// Inicia estructura de descompresion.
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, infile);
	jpeg_read_header(&cinfo, TRUE);
	jpeg_start_decompress(&cinfo);

	// Guarda caracteristicas de la imagen en ImageData.
	width_jpeg = cinfo.output_width;
	height_jpeg = cinfo.output_height;
	row_s = cinfo.output_width * cinfo.output_components;
	buffer = (*cinfo.mem -> alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE , row_s,1);
	*filas_ptr = (JSAMPLE*) malloc(sizeof(JSAMPLE)*row_s*cinfo.output_height);

	for ( int y = 0 ; y < cinfo.output_height ; y++ ) {
		JSAMPLE *row_ptr= &(( *filas_ptr)[y * row_s]);
		jpeg_read_scanlines(&cinfo,buffer,1);
		for ( int x =0; x < row_s ; x++){
			row_ptr[x]=buffer[0][x];

		}
	}
	//imageData.numChannels = cinfo.output_components;

	// Asigna memoria.
	//imageData.data = (unsigned char *)malloc(imageData.width * imageData.height * imageData.numChannels);
	//if (!imageData.data) {
	//	fprintf(stderr, "Error al asignar memoria para los datos de la imagen\n");
	//	fclose(infile);
	//	jpeg_destroy_decompress(&cinfo);
	//	return imageData;
	//}


	// Lee lineas de la imagen y las guarda en imageData.data
	//JSAMPROW row_pointer[1];
	//while (cinfo.output_scanline < cinfo.output_height) {
	//	row_pointer[0] = &imageData.data[(cinfo.output_scanline) * imageData.width * imageData.numChannels];
	//	jpeg_read_scanlines(&cinfo, row_pointer, 1);
	//}

	// Termina descompresiòn y libera recursos.
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(infile);

	return 0; //Retorna datos de la imagen.
}







