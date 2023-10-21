#include <jpeglib.h>

typedef struct {
unsigned char *data;
int width;
int height;
int numChannels;
} ImageData;

unsigned char* JPEGMatrix(const ImageData *imageData);

void writeJPEGImage (const char *filename, unsigned char *rotatedimage, int width, int height);
