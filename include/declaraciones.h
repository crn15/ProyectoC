#include<png.h>
/*
 *Este es el header file del programa
 *
 * */
enum { True = 0 , False = -1 };

int Exist_Dir( char *path );
//Declaraciones PNG
int Flag_Identifier(  int num_argc, char *argv[] , char *path_entrada , char *path_salida  );

int Not_PNG( char *path );

void Read_Png(char *path);
void Png_Write ( char *path_salida , png_bytep *newarray );
//Declaraciones JPEG
int ItsJPEG(const char *archivo);



void writeJPEGImage(const char *filename, JSAMPLE *filas_ptr);
int loadJPEGImage(const char *filename, JSAMPLE **filas_ptr);

JSAMPLE * rotar_jpeg(JSAMPLE * row_pointers);
~                                               

