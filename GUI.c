#include "GUI.h"
//#include <windows.h>
#include <GL/gl.h>
#include "Interface.h"
#include <stdio.h>

#define VK_LBUTTON 5
/*
static GLuint  base;

GLvoid glPrint(const char *fmt,...)
{
    char    text[256];
    va_list    ap;

    if (fmt == NULL) return;

    va_start(ap, fmt);
    vsprintf(text, fmt, ap);
    va_end(ap);
    glPushAttrib(GL_LIST_BIT);
    glListBase(base-32);
    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
    glPopAttrib();
}


GLvoid KillFont(GLvoid)
{
    glDeleteLists(base, 160);
}

GLvoid BuildFont(HDC *hDC)
{
    HFONT  font;

    base = glGenLists(160);
    font = CreateFont(  -20,
                      0,
                      0,
                      0,
                      FW_BOLD,
                      FALSE,
                      FALSE,
                      FALSE,
                      ANSI_CHARSET,
                      OUT_TT_PRECIS,
                      CLIP_DEFAULT_PRECIS,
                      ANTIALIASED_QUALITY,
                      FF_DONTCARE|DEFAULT_PITCH,
                       "Courier New");

    SelectObject(*hDC, font);
    wglUseFontBitmaps(*hDC, 32, 160, base);
}*/

char button(char *name, float x1, float y1, float x2, float y2, float mouse_coord_x, float mouse_coord_y, char *press)
{
    char down=1;

    glColor3f(0.9,0.9,0.9);
    glBegin(GL_QUADS);
        glVertex2f(x1,y1);
        glVertex2f(x2,y1);
        glVertex2f(x2,y2);
        glVertex2f(x1,y2);
    glEnd();

    glColor3f(0,0,0);
    glRasterPos2f(x1,y1);
    //glPrint(name);

    if(mouse_coord_x>=x1 && mouse_coord_x<=x2 && mouse_coord_y>=y1 && mouse_coord_y<=y2)
    {
        if(key(1))
        {
            down=0;
            *press=1;
        }
        else down=1;

        if(*press==1 && down==1)
        {
            *press=0;
            return 1;
        }

        return 0;
    }
    else *press=0;

    return 0;
}
