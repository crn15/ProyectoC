#include <stdlib.h>
#include <stdio.h>
#include <jpeglib.h>
#include <jerror.h>
extern int  rotated_width, rotated_height;
void writeJPEGImage(const char *filename, JSAMPLE *filas_ptr) {
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;

	int quality=100;
	//printf("%d\n", numChannels);
	//Abre el archivo de salida en modo lectura binaria.
	FILE *outfile = fopen(filename, "wb");
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

	row_s = rotated_width * 3;
	row_ptr[0] = &filas_ptr[0];
	while ( cinfo.next_scanline < cinfo.image_height ) {
		jpeg_write_scanlines(&cinfo, row_ptr , 1);
		row_ptr[0] += row_s;
	}

	//JSAMPROW row_pointer[1];
	//int row_stride = width * numChannels;
	/*
	while (cinfo.next_scanline < cinfo.image_height) {
		row_pointer[0] = (JSAMPROW)&rotatedimage[cinfo.next_scanline * row_stride];
	jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}*/

	//Termina compresion y se liberan recursos.
	jpeg_finish_compress(&cinfo);
	fclose(outfile);
	jpeg_destroy_compress(&cinfo);
}


