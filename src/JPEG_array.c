#include <stdlib.h>
#include <stdio.h>
#include <jpeglib.h>
#include <jerror.h>
#include "declaraciones.h"
#include <stddef.h>
// Función para obtener una matriz de píxeles de la imagen.
unsigned char* JPEGMatrix(const ImageData *imageData) {
	unsigned char *pixelArray;
	int imageSize = imageData->width * imageData->height * imageData->numChannels;
	//Asigna memoria para la matriz.
	pixelArray = (unsigned char *)malloc(imageSize * sizeof(unsigned char));
	for (int i = 0; i < imageSize; i++) {
		pixelArray[i] = imageData->data[i];
	}
	return pixelArray; //Retorna matriz de pixeles.
}

