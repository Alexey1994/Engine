#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "Load.h"

typedef struct
{
    GLuint width,
           height;
    GLint  bpp;         /*RGB ��� RGBA*/

    GLubyte *data;

    char *error;
}Image;

Image *load_image(const char *name);
void free_image(Image *data);

#endif
