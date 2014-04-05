#ifndef LOAD_H_INCLUDED
#define LOAD_H_INCLUDED

#include <GL/gl.h>
#include "Math.h"

typedef struct
{
    GLuint width,
           height,
           fps;
}Config;

typedef GLuint Face[4];

typedef struct
{
    char **name;

    GLuint length_faces,
           length_verteces,
           length_normals,
           length_objects,

           *object_indexes;     /*начиная с этого номера строится фейс объекта с номером элемента массива индексов*/

    Point  *verteces;
    Vector *normals;
    Face   *faces;
}Model;

Model* loadOBJ(const char *name);
Config *loadCFG(const char *name);

void free_Model(Model *model);

#endif
