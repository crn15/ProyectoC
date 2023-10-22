#include <stdlib.h>
#include <stdio.h>
#include <jpeglib.h>
#include <jerror.h>

void writeJPEGImage(const char *filename, const unsigned char *rotatedimage, int width, int height, int numChannels) {
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	int quality=95;
	//Abre el archivo de salida en modo lectura binaria.
	FILE *outfile = fopen(filename, "wb");
	if (!outfile) {
		fprintf(stderr, "No se pudo abrir el archivo de salida: %s\n", filename);
		return;
	}
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_set_defaults(&cinfo);

	//Inicia estructura de compresion.
	jpeg_create_compress(&cinfo);
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


