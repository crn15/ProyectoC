#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declaraciones.h"
/*Esta parte se encarga de validar las entradas desde la linea de comandos
 *
 *
 *
 * */

//Defino este enum para poder usar las expresiones True y False a lo largo del codigo
enum True_False { True = 0 , False = -1 };




enum Posible_Flag_Num { HELP = 2 , IMAGE = 6 };
// Solo hay 2 numeros posibles de flags, si se entran menos o mas deberia dar error

// Tiene por argumentos el numero de entradas de la linea, el array con las entradas y los array donde se va a guardar las informacion
int Flag_Identifier(  int num_argc, char *argv[] , char *path_entrada , char *path_salida , char *transformacion ) {
	if ( num_argc > 6 || num_argc < 1 ) {
		printf("Numero invalido de argumentos\n");
		return False;
	}

	switch ( num_argc ) {
		case HELP:
      // Si se ingresa solo un argumento debe ser el de help de otra manera es un error
			if ( strcmp( argv[1] , "-help" ) == True || strcmp( argv[1] , "-h" ) == True) {
				printf("Help\n");
				return True;
			} else {
				printf("Flag invalido\n");
				return False;
			}
			break;
		case IMAGE:
			for ( int i = 1; i < num_argc ; i++ ) {
			       	if ( strcmp( *(argv + i) , "-i") == True ) {
					strcpy( path_entrada , *(argv +i +1));
					printf("%s\n",path_entrada);
					if ( Exist_Dir( path_entrada ) == False ) {
						return False;
					}
				       	//quiero que se salte a la otra iteracion
					i+=1;
			 	} else if ( strcmp( *(argv + i) , "-o") == True) {
					strcpy( path_salida , *(argv +i +1));
					if ( Exist_Dir( path_salida ) == False ) {
                                                return False;
                                        }

					i+=1;
				} else if (  strcmp( *(argv + i), "-r") == True) {
					transformacion = *(argv +i);
				} else {
					printf("Flag no valido, Error\n.");
					return False;
				}
			}
			return True;
			break;
		default:
			printf("Entrada no valida, ver -help\n");
			return False;
	}
}
int main(int argc, char *argv[]) {
      
	char path[35] , out[35] , transform[4];

	//strcpy(path, *(argv +2));
	//printf("%s\n",path);

	int x = Flag_Identifier( argc   , argv , path , out, transform);
	printf("%s\n",path);
    	if ( x == False ) {
		exit(False);
	} else {
		printf("El programa continua\n");
	}

        return 0;
}
