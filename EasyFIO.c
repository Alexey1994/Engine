#include "EasyFIO.h"
#include <stdlib.h>

char *get_name(FILE *f, char *ch)
{
    int k=0;
    char *s=malloc(sizeof(char)*256);

    while(1)
    {
        if(feof(f) || *ch=='\n') break;
        s[k]=*ch;
        k++;
        *ch=fgetc(f);
    }
    s[k]='\0';

    return s;
}

char *get_string(FILE *f, char *ch)
{
    int k=0;
    char *s=malloc(sizeof(char)*256);

    while(1)
    {
        if(feof(f) || *ch==' ' || *ch=='\n') break;
        s[k]=*ch;
        k++;
        *ch=fgetc(f);
    }
    s[k]='\0';

    return s;
}

void skip(FILE *f, char *ch)
{
    while(*ch==' ') *ch=fgetc(f);
}

void skip_string(FILE *f, char *ch)
{
    while(*ch!='\n' && !feof(f)) *ch=fgetc(f);
}

void get_value_GLuint(FILE *f, char *ch, GLuint *value)
{
    char *s;

    skip(f, ch);
    s=get_string(f, ch);
    *value=char_to_GLuint(s);
    free(s);
}

void get_value_GLfloat(FILE *f, char *ch, GLfloat *value)
{
    char *s;

    skip(f, ch);
    s=get_string(f, ch);
    *value=char_to_GLfloat(s);

    free(s);
}
