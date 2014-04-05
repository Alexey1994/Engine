#ifndef IMAGETYPE_H_INCLUDED
#define IMAGETYPE_H_INCLUDED

#include <GL/gl.h>
#include "Image.h"

typedef struct
{
    GLubyte header[6];
    GLuint image_size,
           height,
           width;
    GLint  bpp;             /*24 или 32*/
}TGA;

Image *load_TGA(FILE *f);

#endif
