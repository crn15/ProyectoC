#include <png.h>
#include <stdlib.h>
#include <stdio.h>
#include "declaraciones.h"

extern png_bytep *filas_ptr;

int main(int argc, char *argv[]) {

        char path[35] , out[35] , transform[4];


        int x = Flag_Identifier( argc   , argv , path , out, transform);

        if ( x == False ) {
                exit(False);
        } else {
                printf("El programa continua\n");

		//aqui hay que revisar si es png o jpeg
		if ( Not_PNG( path ) == True ) {
			Read_Png( path );
			// transformacion ( filas_ptr);
			Png_Write( out , filas_ptr );
			// Listo

		} // aqui iria la funcion de comprobar si jpeg
        }

        return 0;
}

