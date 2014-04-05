#include "Load.h"
#include "Math.h"
#include "EasyFIO.h"
#include <GL/glext.h>
#include "Image.h"
#include <stdlib.h>

Config *loadCFG(const char *name)
{
    Config *tmp=malloc(sizeof(Config));
    char *ch=malloc(sizeof(char)), *s1, *s2;
    FILE *f;
    f=fopen(name, "rt");
    if(f==0)
    {
        tmp->width=640;
        tmp->height=480;
        tmp->fps=60;

        return tmp;
    }

    *ch=fgetc(f);
    while(1)
    {
        if(feof(f)) break;
        skip(f, ch);
        if(*ch=='#') skip_string(f, ch);
        else
        {
            s1=get_string(f, ch);
            skip(f, ch);
            s2=get_string(f, ch);

            if(string_comparision(s1, "width")) tmp->width=char_to_GLuint(s2);
            else if(string_comparision(s1, "height")) tmp->height=char_to_GLuint(s2);
            else if(string_comparision(s1, "fps")) tmp->fps=char_to_GLuint(s2);

            free(s1);
            free(s2);
        }
        *ch=fgetc(f);
    }

    free(ch);
    fclose(f);
    return tmp;
}

Model* loadOBJ(const char *name)
{
    FILE *f=fopen(name, "rt");
    Model *model;
    char *ch;
    GLuint l_faces=0, l_verteces=0, l_objects=0;
    GLuint i=0, j=0, k=0;
    Vector *normals;
    Face *faces;
    Point *verteces;
    Vector a,b,c;

    if(f==0) return 0;
    model=malloc(sizeof(Model));
    ch=malloc(sizeof(char));

    while(1)
    {
        *ch=fgetc(f);
        if(feof(f)) break;

        if(*ch=='v') l_verteces++;
        else
        if(*ch=='f') l_faces++;
        else
        if(*ch=='o') l_objects++;
        skip_string(f, ch);
    }
    fclose(f);

    faces=malloc(sizeof(Face)*l_faces);
    verteces=malloc(sizeof(Point)*l_verteces);
    normals=malloc(sizeof(Vector)*l_faces);
    model->name=malloc(sizeof(char)*l_objects);
    model->object_indexes=malloc(sizeof(GLuint)*l_objects);

    f=fopen(name, "rt");

    while(1)
    {
        *ch=fgetc(f);
        if(feof(f)) break;
        if(*ch=='f')
        {
            *ch=fgetc(f);
            if(*ch!=' ') break;

            get_value_GLuint(f, ch, faces[i]);
            if(*ch!='\n')
                get_value_GLuint(f, ch, faces[i]+1);
            else faces[i][1]=0;
            if(*ch!='\n')
                get_value_GLuint(f, ch, faces[i]+2);
            else faces[i][2]=0;
            if(*ch!='\n')
                get_value_GLuint(f, ch, faces[i]+3);
            else faces[i][3]=0;

            i++;
        }
        else
        if(*ch=='v')
        {
            *ch=fgetc(f);
            if(*ch!=' ') break;

            get_value_GLfloat(f, ch, verteces[j]);
            get_value_GLfloat(f, ch, verteces[j]+1);
            get_value_GLfloat(f, ch, verteces[j]+2);

            j++;
        }
        else
        if(*ch=='o')
        {
            *ch=fgetc(f);
            skip(f, ch);
            model->name[k]=get_name(f, ch);
            model->object_indexes[k]=i;
            k++;
        }
        else
            skip_string(f, ch);
    }

/*-----------------------NORMALS---------------*/

    for(i=0; i<l_faces; i++)
    {
        a[0]=verteces[faces[i][2]-1][0] - verteces[faces[i][0]-1][0];
        a[1]=verteces[faces[i][2]-1][1] - verteces[faces[i][0]-1][1];
        a[2]=verteces[faces[i][2]-1][2] - verteces[faces[i][0]-1][2];

        b[0]=verteces[faces[i][1]-1][0] - verteces[faces[i][0]-1][0];
        b[1]=verteces[faces[i][1]-1][1] - verteces[faces[i][0]-1][1];
        b[2]=verteces[faces[i][1]-1][2] - verteces[faces[i][0]-1][2];

        VectorOrtogonalize(a,b,c);
        VectorNormalize(c);
        VectorCopy(normals[i],c);
    }

    model->length_faces=l_faces;
    model->length_verteces=l_verteces;
    model->length_objects=l_objects;
    model->length_normals=l_faces;
    model->normals=normals;
    model->faces=faces;
    model->verteces=verteces;

    fclose(f);

    return model;
}

void free_Model(Model *model)
{
    GLuint i;

    free(model->faces);
    free(model->verteces);
    free(model->normals);
    free(model->object_indexes);
    for(i=0; i<model->length_objects; i++)
        free(*(i+model->name));
    free(model->name);
}

GLuint load_texture(const char *name)
{
    GLint out_type;
    Image *image=load_image(name);
    GLuint texture_id;

    if(image==0) return 0;
    if(image->bpp==GL_RGB) out_type=GL_BGR;
    if(image->bpp==GL_RGBA) out_type=GL_BGRA;

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_LINEAR_MIPMAP_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, image->bpp, image->width, image->height, 0, out_type, GL_UNSIGNED_BYTE, image->data);

    free_image(image);
    return texture_id;
}
