#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include "Math.h"

typedef struct
{
    Vector4 symbol[256];
    char *name;
}Font;

Font *load_font(const char *name);
void free_font(Font *font);

#endif
