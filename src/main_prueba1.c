#include <png.h>
#include <stdlib.h>
#include <stdio.h>
#include "declaraciones.h"

extern png_bytep *filas_ptr;
//extern png_bytep *rotated_row_pointers;
int main(int argc, char *argv[]) {

        char path[35] , out[35] ;


        int x = Flag_Identifier( argc   , argv , path , out);

        if ( x == False ) {
                exit(False);
        } else {
                printf("El programa continua\n");

		//aqui hay que revisar si es png o jpeg
		if ( Not_PNG( path ) == True ) {
			//Lectura del png y asignacion del array
			Read_Png( path );
			//Rotacion del png
			png_bytep *rotated_pointers = rotacion(filas_ptr );
			//Escritura del png
			Png_Write( out , rotated_pointers );
			// Listo

		} else if ( ItsJPEG ( path ) == True ) {
			printf("Es un jpeg\n");
			//Llamada a funcion que carga la imagen
			ImageData imageData = loadJPEGImage(path);
			if (imageData.data != NULL){
				// Llamada a funcion que retorna matriz de píxeles.
				unsigned char *pixelArray = JPEGMatrix(&imageData);
				printf("%d\n",pixelArray[0]);
				//Llamada a funcion que escribe la imagen.
				writeJPEGImage(out, pixelArray, imageData.width, imageData.height);
				printf("Imagen rotada guardada como %s\n", out);
				// Libera la memoria de la matriz de píxeles.
				free(pixelArray);
				// Libera la memoria de los datos de la imagen.
				free(imageData.data);

			} 
		}

        return 0;
	}
}

