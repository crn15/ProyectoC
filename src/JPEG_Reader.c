#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <jerror.h>
#include "declaraciones.h"
int width_jpeg, height_jpeg;
// Función para cargar imagen JPEG.
int loadJPEGImage(const char *filename, JSAMPLE **filas_ptr) {
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	// JSAMPARRAY es una estructura de la libreria para indicar un arreglo bidimensional, en este caso se usa para guardar lineas de pixels de la imagen

	JSAMPARRAY buffer;
	// Variable temporal para guardar el ancho en bytes de la imagen
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
	// temporalmente se posiciona memoria para una linea de pixels
	buffer = (*cinfo.mem -> alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE , row_s,1);
	// Memoria para el array final
	*filas_ptr = (JSAMPLE*) malloc(sizeof(JSAMPLE)*row_s*cinfo.output_height);
	// En este loop se transfiere los datos de cada linea de la imagen del buffer temporal al array
	for ( int y = 0 ; y < cinfo.output_height ; y++ ) {
		JSAMPLE *row_ptr= &(( *filas_ptr)[y * row_s]);
		jpeg_read_scanlines(&cinfo,buffer,1);
		for ( int x =0; x < row_s ; x++){
			row_ptr[x]=buffer[0][x];

		}
	}


	// Termina descompresiòn y libera recursos.
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(infile);

	return True; 
}







