#include<png.h>
enum { True = 0 , False = -1 };
int Exist_Dir( char *path );
int Not_PNG( char *path );
void Read_Png(char *path );
void Png_Write ( char *path_salida , png_bytep *newarray );
int Flag_Identifier(  int num_argc, char *argv[] , char *path_entrada , char *path_salida , char *transformacion );
