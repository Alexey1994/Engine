#ifndef EASYFIO_H_INCLUDED
#define EASYFIO_H_INCLUDED

#include <stdio.h>
#include <GL/gl.h>

char *get_name(FILE *f, char *ch);
char *get_string(FILE *f, char *ch);
void skip(FILE *f, char *ch);
void skip_string(FILE *f, char *ch);
void get_value_GLuint(FILE *f, char *ch, GLuint *value);
void get_value_GLfloat(FILE *f, char *ch, GLfloat *value);

#endif
