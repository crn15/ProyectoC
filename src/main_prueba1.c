#include <png.h>
#include <stdlib.h>
#include <stdio.h>
#include "declaraciones.h"

extern png_bytep *filas_ptr;
extern png_bytep *rotated_row_pointers;
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
			rotacion( rotated_row_pointers);
			Png_Write( out , rotated_row_pointers );
			// Listo

		} // aqui iria la funcion de comprobar si jpeg
        }

        return 0;
}

