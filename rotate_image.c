#include <stdlib.h>
#include <png.h>
#include "rotate_image.h"

void rotate_image(int width, int height, png_bytep *row_pointers, char *output_file) {
    int rotated_width = height;
    int rotated_height = width;

    png_bytep *rotated_row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * rotated_height);
    for (int y = 0; y < rotated_height; y++) {
        rotated_row_pointers[y] = (png_byte*) malloc(rotated_width * 4);
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int rotated_x = height - 1 - y;
            int rotated_y = x;

            png_bytep pixel = &(row_pointers[y][x * 4]);
            png_bytep rotated_pixel = &(rotated_row_pointers[rotated_y][rotated_x * 4]);

            for (int c = 0; c < 4; c++) {
                rotated_pixel[c] = pixel[c];
            }
        }
    }

    write_png_file(output_file, rotated_width, rotated_height, rotated_row_pointers);

    for (int y = 0; y < rotated_height; y++) {
        free(rotated_row_pointers[y]);
    }
    free(rotated_row_pointers);
}
