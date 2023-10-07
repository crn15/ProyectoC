#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

extern int errno;
/*Esta funcion comprueba si el directorio existe
 *Recibe por parametro el path
 *retorno 0 en caso que exista y -1 en caso de fallo
 * */
int Exist_Dir( char *path ) {
	FILE * fp;

        fp = fopen( path , "rb");
        if ( !fp ) {
                perror("Error");
		return -1;
        } else {
                fclose (fp);
        }

        return 0;

}


