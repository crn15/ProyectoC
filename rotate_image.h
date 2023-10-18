#include <png.h>

void rotate_image(int width, int height, png_bytep *row_pointers, char *output_file);
int write_png_file(char *filename, int width, int height, png_bytep *row_pointers);
int read_png_file(char *filename, int *width, int *height, png_bytep **row_pointers);
