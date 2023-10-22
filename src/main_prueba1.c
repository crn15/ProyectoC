#include <png.h>
#include <stdlib.h>
#include <stdio.h>
#include "declaraciones.h"

extern png_bytep *filas_ptr;
JSAMPLE *filas_jpeg = NULL;
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
			if (  loadJPEGImage(path , &filas_jpeg) != False ) {
				printf("Se realizo la lectura de la imagen con exito\n");
				// Se llama a la funcion que rota al jpeg y devuelve el array rotado
				JSAMPLE *rotated_jpeg = rotar_jpeg( filas_jpeg);
				//Se escribe la nueva imagen
				writeJPEGImage( out , rotated_jpeg);
				printf("Su imagen fue rotada y se guardo en %s \n" , out);
			}else { 
				printf("Error al cargar imagen\n");
				return False;
			}	
		}

        return True;
	}
}

