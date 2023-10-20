#include <stdio.h>
#include <stdlib.h>
#include <png.h>

//extern png_bytep *filas_ptr;
extern int width, height,num_channels;
extern png_byte color_type , bits_d;
int rotated_width, rotated_height;
//png_bytep * rotated_row_pointers = NULL;

png_bytep* rotacion( png_bytep *matrix) {
	// Variables globales para poder usarlas en la funcion de escritura
	 rotated_width = height;
	 
  	 rotated_height = width;

  // reservar memoria para almacenar la imagen rotada
 	 png_bytep *rotated_row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * rotated_height); //asigna memoria para arreglo de punteros a las filas de pixeles de la imagen rotada - puntero a puntero
	 //int bits_depth = (int)bits_d;
	 //size_t rotated_row_size = rotated_width * bits_depth * num_channels / 8;

	 for (int y = 0; y < rotated_height; y++) {
		 //rotated_row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png, info));
		 rotated_row_pointers[y] = (png_byte *)malloc(rotated_width*4);
	 }

	 for (int y = 0; y < height; y++) {
    //int rotated_x = height - y - 1;
    //int rotated_y = x;
         for (int x = 0; x < width; x++) {
		 
		 int rotated_x = height - 1 - y;
		 int rotated_y = x;
		 png_bytep pixel = &(matrix[y][x*4]); // obtener pixel original
	       	 png_bytep rotated_pixel = &(rotated_row_pointers[rotated_y][rotated_x*4]); // obtener pixel rotado
	        //rotated_pixel = pixel;
		// copiar el pixel original en la posición correspondiete en la imagen rotada
		 for (int c = 0; c < num_channels; c++) {
        	//	rotated_row_pointers[x][c] = row_pointers[y][x * num_channels + c];
			rotated_pixel[c] = pixel[c];
      }
    }
  }     
	 // Liberamos el espacio de la matrix sin rotar
	 for ( int i = 0 ; i < height ; i++ ) {
		 free(matrix[i]);
	 }

	 free(matrix);
	 matrix = NULL;
	 //Se retorna la matrix rotada
	 
	 return rotated_row_pointers;
}

