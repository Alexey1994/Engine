#include "Font.h"
#include <stdio.h>
#include <stdlib.h>

Font *load_font(const char *name)
{
    FILE *f=fopen(name, "rb");
    Font *font=0;
    char verify[]="FONT", temp[8];
    int i;

    if(f==0) return 0;

    for(i=0; i<4; i++) temp[i]=fgetc(f);
    temp[i]='\0';
    if(!string_comparision(verify, temp)) return 0;

    font=malloc(sizeof(Font));

    string_copy(font->name, name);

    for(i=0; i<256; i++)
    {
        fread(font->symbol[i], 0, sizeof(GLfloat), f);
        fread(font->symbol[i]+1, 0, sizeof(GLfloat), f);
        fread(font->symbol[i]+2, 0, sizeof(GLfloat), f);
        fread(font->symbol[i]+3, 0, sizeof(GLfloat), f);
    }

    fclose(f);
    return font;
}
