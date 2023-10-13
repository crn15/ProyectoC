#include <stdio.h>
#include <stdlib.h>
#include <png.h>

int main(int argc, char * argv[]) {
  // Cargar los paths de la imagen original y la rotada
  const char * input_path = argv[1];
  const char * output_path = argv[2];
  
  // read binary de archivo de entrada devuelve puntero a estrucutra tipo FILE
  FILE * file = fopen(input_path, "rb");
  if (!file) {
    fprintf(stderr, "Error al abrir el archivo de entrada\n");
    return 1;
  }

  // función de libpng, requiere vincularla con -lpng al compilar
  // declaración de puntero png para estructura png_struct
  // png_create_read_struct inicializa estructura para lectura de archivo PNG
  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png) { // verifica si png fue inicializado correctamente, si falló png_create_read_struct devuelve NULL
    fclose(file);
    fprintf(stderr, "Error al inicializar la estructura PNG\n");
    return 1;
  }

  png_infop info = png_create_info_struct(png);

  if (!info) {
    png_destroy_read_struct(&png, NULL, NULL); // libera estructura de lectura del archivo, con &png recibe puntero al puntero png
    fclose(file);
    fprintf(stderr, "Error inicializando estructura info de PNG\n");
  }


  // configurar función de salto para manejo de errores de lectura
  if (setjmp(png_jmpbuf(png))) {
    png_destroy_read_struct(&png, NULL, NULL);
    fclose(file);
    fprintf(stderr, "Error de lectura del archivo PNG\n");
  }
  

  // inicializar la lectura y cargar la imagen
  png_init_io(png, file);
  png_read_info(png, info);

  // obtener ancho y altura de la imagen original
  int width = png_get_image_width(png, info); 
  int height = png_get_image_height(png, info); 

  // obtener información particular de archivo PNG (proviene de encabezado obtenido con png_create_info_struct)
  // sirve para reproducir fielmente la imagen rotada
  int color_type = png_get_color_type(png, info); // tipo de color
  int bit_depth = png_get_bit_depth(png, info); // profundidad de bits
  int num_channels = (color_type == PNG_COLOR_TYPE_RGBA) ? 4 : 3; // cantidad de canales de color, 3 para RGB o 4 para RGBA

  // memory allocation para reservar memoria para almacenar datos de pixeles
  png_bytep * row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);

  for (int y = 0; y < height; y++) {
    row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png, info));
  } 
  
  // leer los datos de pixeles
  png_read_image(png, row_pointers);



  // ===== Crear una nueva imagen rotada =====

  // intercambiar ancho y alto
  int rotated_width = height;
  int rotated_height = width;
  //printf("width: %d\nheight: %d\nrotated_width: %d\nrotated height: %d\n", width, height, rotated_width, rotated_height);


  // reservar memoria para almacenar la imagen rotada
  png_bytep * rotated_row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * rotated_height);

  for (int y = 0; y < rotated_height; y++) {
    rotated_row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png, info));
  }

  // copiar y rotar los datos de los pixeles intercambiando filas y columnas
  for (int y = 0; y < height; y++) {
    //int rotated_x = height - y - 1;
    //int rotated_y = x;
    for (int x = 0; x < width; x++) {

      png_bytep pixel = &(row_pointers[y][x]); // obtener pixel original
      
      int rotated_x = height - y - 1;
      int rotated_y = x;

      //printf("x: %d, rotated_y: %d\n", x, rotated_y);
      //printf("y: %d, rotated_x: %d\n", y, rotated_x);

      png_bytep rotated_pixel = &(rotated_row_pointers[rotated_y][rotated_x]); // obtener pixel rotado


      // copiar el pixel original en la posición correspondiete en la imagen rotada
      for (int c = 0; c < num_channels; c++) {
        //rotated_row_pointers[x][c] = row_pointers[y][x * num_channels + c];
        rotated_pixel[c] = pixel[c];
      }
    }
  }


  // crear archivo para guardar la imagen rotada
  FILE * output_file = fopen(output_path, "wb"); // write binary

  if (!output_file) {
    fprintf(stderr, "Error al abrir el archivo de destino para la imagen rotada\n");
    return 1;
  }

  // inicializar una estructura para la escritura PNG
  png_structp png_write = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_write) {
    fclose(output_file);
    fprintf(stderr, "Error inicializando estructura de escritura PNG");
    return 1;
  }


  // inicializar la escritura
  png_init_io(png_write, output_file);


  // establecer la información de imagen PNG en el nuevo archivo rotado
  png_set_IHDR(png_write, info, rotated_width, rotated_height, bit_depth, color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

  // escribir la información de la imagen
  png_write_info(png_write, info);

  // escribir los datos de los pixeles de la imagen rotada
  png_write_image(png_write, rotated_row_pointers);

  // finalizar escritura
  png_write_end(png_write, NULL);


  // limpiar y liberar recursos y memmoria

  png_destroy_read_struct(&png, &info, NULL);
  png_destroy_write_struct(&png_write, &info);
  fclose(file);
  fclose(output_file);


  for (int y = 0; y < rotated_height; y++) {
    free(rotated_row_pointers[y]);
  }
  
  free(rotated_row_pointers);

  for (int y = 0; y < height; y++) {
    free(row_pointers[y]);
  }

  free(row_pointers);




  return 0;

}

