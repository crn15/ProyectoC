#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include "rotate_image.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    char *input_file = argv[1];
    char *output_file = argv[2];

    int width, height;
    png_bytep *row_pointers;

    if (read_png_file(input_file, &width, &height, &row_pointers)) {
        return 1;
    }

    rotate_image(width, height, row_pointers, output_file);

    for (int y = 0; y < height; y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);

    return 0;
}
