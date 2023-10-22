#include <stdlib.h>
#include <stdio.h>
#include <jpeglib.h>
#include <jerror.h>
extern int  rotated_width, rotated_height;
void writeJPEGImage(const char *filename, JSAMPLE *filas_ptr) {
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;

	int quality=100;

	//Abre el archivo de salida en modo lectura binaria.
	FILE *outfile = fopen(filename, "wb");
	//JSAMPROW es un tipo de dato de la libreria que indica un puntero a una fila de datos tipo pixel
	JSAMPROW row_ptr[1];
	int row_s;

	if (!outfile) {
		fprintf(stderr, "No se pudo abrir el archivo de salida: %s\n", filename);
		return;
	}
	cinfo.err = jpeg_std_error(&jerr);
	

	//Inicia estructura de compresion.
	jpeg_create_compress(&cinfo);
	jpeg_stdio_dest(&cinfo, outfile);
	//Configura caracteristicas de la imagen.
	cinfo.image_width = rotated_width;
	cinfo.image_height = rotated_height;
	cinfo.input_components = 3;
	cinfo.in_color_space = JCS_RGB;

	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, quality, TRUE);

	jpeg_start_compress(&cinfo, TRUE);
	// Esta linea calcula el numero de bytes en una linea de la nueva imagen.Recordar que cada pixel consta de 3 bytes.
	row_s = rotated_width * 3;

	// En este caso row_ptr funciona como un index, incia en el incio del nuevo array osea la primera fila de pixels
	row_ptr[0] = &filas_ptr[0];
	while ( cinfo.next_scanline < cinfo.image_height ) {
		//Escribo la nueva linea de pixels 
		jpeg_write_scanlines(&cinfo, row_ptr , 1);
		//Le sumo una fila al puntero, recordar que row_ptr es un ** aqui realmente estoy moviendome de una fila a otra
		row_ptr[0] += row_s;
	}



	//Termina compresion y se liberan recursos.
	jpeg_finish_compress(&cinfo);
	fclose(outfile);
	jpeg_destroy_compress(&cinfo);
	free(filas_ptr);
}


