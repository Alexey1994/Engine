#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

//#include <windows.h>
#include <GL/gl.h>
#include "List.h"

//GLvoid BuildFont(HDC *hDC);
//GLvoid KillFont(GLvoid);

GLvoid glPrint(const char *fmt,...);
GLvoid glPrintList(List *list);

char button(char *name, float x1, float y1, float x2, float y2, float mouse_coord_x, float mouse_coord_y, char *press);

#endif
