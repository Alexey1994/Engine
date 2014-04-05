#include <stdlib.h>
#include <stdio.h>
#include "Image.h"
#include "ImageType.h"
#include "Math.h"

Image *load_image(const char *name)
{
    Image *image=0;
    char type[4]="tga";
    FILE *f=fopen(name, "rb");

    if(string_comparision(type, "tga")) image=load_TGA(f);

    fclose(f);
    return image;
}

void free_image(Image *data)
{
    free(data->data);
    free(data->error);
    free(data);
}

Image *load_TGA(FILE *f)
{
    TGA tga;
    Image *image=0;
    GLubyte compessed[]={0,0,10,0,0,0,0,0,0,0,0,0},
            uncompessed[]={0,0,2,0,0,0,0,0,0,0,0,0},
            head[12];

    if(f==0) return 0;

    if(fread(head, 12, 1, f)==0) return 0;

    if(memory_comparision(head, compessed, 12))
    {

    }
    else
    if(memory_comparision(head, uncompessed, 12))
    {
        if(fread(tga.header, 6, 1, f)==0) return 0;

        tga.width=tga.header[1]*256+tga.header[0];
        tga.height=tga.header[3]*256+tga.header[2];
        tga.bpp=tga.header[4];

        if(tga.width<1 || tga.height<1 || (tga.bpp!=32 && tga.bpp!=24)) return 0;

        image=malloc(sizeof(Image));

        image->height=tga.height;
        image->width=tga.width;
        if(tga.bpp==32) image->bpp=GL_RGBA;
        if(tga.bpp==24) image->bpp=GL_RGB;

        tga.image_size=tga.height*tga.width*tga.bpp/8;
        image->data=malloc(tga.image_size);
        if(image->data==0)
        {
            free(image);
            return 0;
        }

        if(fread(image->data, 1, tga.image_size, f)!=tga.image_size)
        {
            free(image->data);
            free(image);
            return 0;
        }
    }
    else return 0;

    return image;
}
