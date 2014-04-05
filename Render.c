#include "Render.h"
#include <GL/gl.h>

void draw_obj(const Model *obj)
{
    GLfloat specref[]={1,1,1,1};
    int i, length=obj->length_faces;
    Vector *normals=obj->normals;
    Point *verteces=obj->verteces;
    Face *faces=obj->faces;

    glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
    glMateriali(GL_FRONT, GL_SHININESS, 128);

    glBegin(GL_QUADS);
    for(i=0; i<length; i++)
    {
        /*if(faces[i][1]==0)
        {
            glBegin(GL_POINTS);
                glVertex3fv(verteces[faces[i][0]-1]);
            glEnd();
        }
        else if(faces[i][2]==0)
        {
            glBegin(GL_LINES);
                glVertex3fv(verteces[faces[i][0]-1]);
                glVertex3fv(verteces[faces[i][1]-1]);
            glEnd();
        }*/
        if(faces[i][3]==0)
        {
            glNormal3fv(normals[i]);

            glEnd();
            glBegin(GL_TRIANGLES);
                glTexCoord2f(0,0); glVertex3fv(verteces[faces[i][0]-1]);
                glTexCoord2f(0,1); glVertex3fv(verteces[faces[i][1]-1]);
                glTexCoord2f(1,1); glVertex3fv(verteces[faces[i][2]-1]);
            glEnd();
            glBegin(GL_QUADS);
        }
        else
        {
            glNormal3fv(normals[i]);

            glTexCoord2f(0,0); glVertex3fv(verteces[faces[i][0]-1]);
            glTexCoord2f(0,1); glVertex3fv(verteces[faces[i][1]-1]);
            glTexCoord2f(1,1); glVertex3fv(verteces[faces[i][2]-1]);
            glTexCoord2f(1,0); glVertex3fv(verteces[faces[i][3]-1]);
        }
    }
    glEnd();
}
