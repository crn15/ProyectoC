// Programa que implementa el algoritmo de rotación de la imagen 90 grados a la derecha
// El algoritmo consiste en reasignar la información de la matriz de pixeles por filas
// de las coordenadas originales a las correspondientes coordenadas de la imagen rotada

#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include <jpeglib.h>

extern int width, height,num_channels;
extern png_byte color_type , bits_d;
int rotated_width, rotated_height;

// Función de rotación recibe puntero a matriz de pixles de imagen original y devuelve puntero a la imagen rotada
png_bytep* rotacion( png_bytep *matrix) {
	 // Nuevas dimensiones
	 rotated_width = height;
  	 rotated_height = width;

	 // Reservar memoria para areglo de punteros a filas de pixeles de la imagen rotada (puntero doble)
 	 png_bytep *rotated_row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * rotated_height);
	 
	 // Asignar memoria para cada puntero que apunta la información de las filas de pixeles
	 for (int y = 0; y < rotated_height; y++) {
		 rotated_row_pointers[y] = (png_byte *)malloc(rotated_width*4); // 4 canales para RGBA
	 }

	 // ========================================================
	 // =       Implementación del algoritmo de rotación       =
	 // ========================================================

	 // Se recorren todas las filas según la altura de la imagen original
	 for (int y = 0; y < height; y++) {
		 // Dentro de cada fila, se recorren todas las abscisas (ancho)
		 for (int x = 0; x < width; x++) {
			 // Se calcula las coordenadas correspondietes de la imagen rotada a partir de las cordenadas originales
			 // Rotar 90° a la derecha equivale a transponer la matriz de pixeles y luego invertir el orden de las columnas 
			 int rotated_x = height - 1 - y; // Para obtener la coordenada 'x' rotada se invierte orden de columnas
			 int rotated_y = x; // La coordenada 'y' rotada corresponde a la coordenada 'x' original
			 
			 // Se obtienen los punteros a la información de cada pixel para la reasignación de la original a la rotada
			 png_bytep pixel = &(matrix[y][x*4]);
	       	 	 png_bytep rotated_pixel = &(rotated_row_pointers[rotated_y][rotated_x*4]);
			 
			 // Se copia información del pixel original en el pixel rotado		 
			 for (int c = 0; c < num_channels; c++) {
				 rotated_pixel[c] = pixel[c];
			 }
		 }
	 }     

	 // Liberar el espacio de la matriz original
	 for ( int i = 0 ; i < height ; i++ ) {
		 free(matrix[i]);
	 }
	 free(matrix);
	 matrix = NULL;

	 // Retornar puntero a las filas de la matriz rotada
	 return rotated_row_pointers;
}

// Función para rotar imagen en formato JPEG (mismo algoritmo de rotación)
JSAMPLE * rotar_jpeg(JSAMPLE * row_pointers) {
	int rotated_width = height;
	int rotated_height = width;

	JSAMPLE * rotated_row_pointers = (JSAMPLE *)malloc(sizeof(JSAMPLE) * rotated_width * rotated_height * 3);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int rotated_x = height - 1 - y;
			int rotated_y = x;

			JSAMPLE *pixel = &(row_pointers[(y * width + x) * 3]);
			JSAMPLE *rotated_pixel = &(rotated_row_pointers[(rotated_y * rotated_width + rotated_x) * 3]);

			for (int c = 0; c < 3; c++) {
				rotated_pixel[c] = pixel[c];			
			}
		}
	}

	free(row_pointers);

	return rotated_row_pointers;

}
