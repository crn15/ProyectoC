#include<png.h>
<<<<<<< HEAD
enum { True = 0 , False = -1 };

int Exist_Dir( char *path );

int Flag_Identifier(  int num_argc, char *argv[] , char *path_entrada , char *path_salida , char *transformacion );

int Not_PNG( char *path );

void Read_Png(char *path);
void Png_Write ( char *path_salida , png_bytep *newarray );
