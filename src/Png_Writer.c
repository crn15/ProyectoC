#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include "declaraciones.h"

extern  int  rotated_width, rotated_height;
extern png_byte color_type, bits_d ;



void Png_Write ( char *path_salida , png_bytep *newarray ) {
	FILE* output = fopen( path_salida , "wb");
	if ( output == NULL) {
		fprintf(stderr, "Error al encontrar el directorio de salida\n");
		return;
	}

	

	//Creo la estructura para escribir

	png_structp pngw_ptr =  png_create_write_struct(PNG_LIBPNG_VER_STRING , NULL , NULL , NULL );
	if ( pngw_ptr == NULL ) {
		fprintf(stderr, "Error al escribir el png\n");
                return;

	}

	//De nuevo debo crear la estructura que maneja la info del png

	png_infop winfo_ptr = png_create_info_struct(pngw_ptr);

	if ( winfo_ptr == NULL ) {
		//Este paso es importante para liberar la memoria
		png_destroy_write_struct( &pngw_ptr , NULL);
		fprintf(stderr, "Error al escribir el png\n");
                return;

	}

	//Esta funcion maneja las salidas y entradas del png

	png_init_io( pngw_ptr , output);
	// png_set_IHDR sirve para definir el header que hace a la imagen un png, se deben definir los mismos parametros que antes se habian leido de la imagen
	
	png_set_IHDR(pngw_ptr , winfo_ptr , rotated_width, rotated_height , bits_d , PNG_COLOR_TYPE_RGBA , PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	
	//Guardo la info en el header de mi nuevo png
	png_write_info(pngw_ptr , winfo_ptr);
	// Ahora escribo mi imagen usando la matriz de bytes ya modificada
	png_write_image(pngw_ptr , newarray);

	png_write_end(pngw_ptr , NULL);

	png_destroy_write_struct( &pngw_ptr , &winfo_ptr );

	fclose(output);

	for ( int i = 0 ; i < rotated_height ; i++) {
                free(newarray[i]);
        }

        free(newarray);
	newarray = NULL;


	printf("Su imagen fue rotada \n");

}

