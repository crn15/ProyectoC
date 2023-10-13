#include <png.h>

#include <stdlib.h>
#include <stdio.h>
#include "declaraciones.h"
/*Esta funcion revisa si el archivo es un png
 *resibe el path del archivo
 *retorna True or False segun sea el caso
 *
 * */
int Not_PNG( char *path ) {
	FILE *fp = fopen( path , "rb" );
        if (!fp) {
                return False;
        }
        unsigned char header[8];

        if ( fread(header,1, sizeof(header), fp)< 8) {
                fclose(fp);
                return True;
        }
        if ( png_sig_cmp(header,0,8) ) {
                fclose(fp);
                return False ;
        }
	printf("IS PNG.\n");
	fclose(fp);
	return True;


}
