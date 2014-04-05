#include <GL/gl.h>
#include "Render.h"
//#include <windows.h>
#include "GUI.h"
#include "List.h"
#include "Font.h"

void draw(GLfloat aspect, GLfloat mouse_coord_x, GLfloat mouse_coord_y, GLboolean *bQuit)
{
    static char verify=1, b[4];
    static List list;
    static Font *f;
    static GLfloat matrix[]={1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
    static char a[50]={0};

    matrix[0]=1.0f/aspect;
    if(verify)
    {
        f=load_font("a.fnt");
       // if(f==0) printf("error");

        list.begin=0;
        list.size=0;

        insert_list(&list, '1', 0);
        insert_list(&list, '2', 0);
        insert_list(&list, '3', 0);

        get_array(&list, b);

        verify=0;
    }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadMatrixf(matrix);
        glRasterPos2f(0,0);
        //glPrint(b);


    /*button("",-1,-1,1,1,mouse_coord_x,mouse_coord_y,a+5);*/
static float i=0;
        if(button("EXIT", 0.85*aspect+i, 0.95, 0.95*aspect+i, 1, mouse_coord_x, mouse_coord_y, a))
            *bQuit=GL_TRUE;
            i+=0.001;
bQuit=GL_TRUE;
    glPopMatrix();
}
