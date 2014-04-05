#include "Math.h"
#include <math.h>
#include <stdlib.h>

/*---------------------------math-----------------------------*/

void VectorOrtogonalize(const Vector a, const Vector b, Vector normale)
{
    normale[0]=a[1]*b[2]-a[2]*b[1];
    normale[1]=a[2]*b[0]-a[0]*b[2];
    normale[2]=a[0]*b[1]-a[1]*b[0];
}

void VectorNormalize(Vector a)
{
    GLfloat length=sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);
    a[0]*=length;
    a[1]*=length;
    a[2]*=length;
}

GLfloat power_10(int n)
{
    int i=0;
    GLfloat temp=1;

    if(n>0)
        for(i=0; i<n; i++)
            temp*=10;
    else
    if(n<0)
        for(i=0; i>n; i--)
            temp/=10;

    return temp;
}

/*---------------------------convertors------------------------*/

GLuint char_to_GLuint(char *ch)
{
    GLuint temp=0;
    int i=0, size=0;

    while(ch[size])
        size++;

    while(ch[i])
    {
        temp+=(ch[i]-'0')*power_10(size-i-1);
        i++;
    }

    return temp;
}

GLint char_to_GLint(char *ch)
{
    GLint temp=0;
    int i, size=0;

    if(ch[0]=='-')
    {
        i=1;
        while(ch[size])
            size++;

        while(ch[i])
        {
            temp+=(ch[i]-'0')*power_10(size-i-1);
            i++;
        }
        return -temp;
    }
    else
    {
        i=0;
        while(ch[size])
            size++;

        while(ch[i])
        {
            temp+=(ch[i]-'0')*power_10(size-i-1);
            i++;
        }
        return temp;
    }
}

GLfloat char_to_GLfloat(char *ch)
{
    GLfloat temp=0;
    int i, num_to_point=1;

    if(ch[0]=='-')
    {
        i=1;

        while(ch[num_to_point]!='.' && ch[num_to_point]!='\0')
            num_to_point++;

        while(ch[i]!='.')
        {
            temp+=(ch[i]-'0')*power_10(num_to_point-i-1);
            i++;
        }
        i++;
        while(ch[i])
        {
            temp+=(ch[i]-'0')*power_10(num_to_point-i);
            i++;
        }

        return -temp;
    }
    else
    {
        i=0;

        while(ch[num_to_point]!='.' && ch[num_to_point]!='\0')
            num_to_point++;

        while(ch[i]!='.')
        {
            temp+=(ch[i]-'0')*power_10(num_to_point-i-1);
            i++;
        }
        i++;
        while(ch[i])
        {
            temp+=(ch[i]-'0')*power_10(num_to_point-i);
            i++;
        }

        return temp;
    }
}

/*------------------------------strings--------------------------------*/

void string_copy(char *s1, const char *s2)
{
    int size=string_length(s2), i;
    free(s1);
    s1=malloc(size);

    for(i=0; i<size; i++)
        s1[i]=s2[i];
}

GLubyte string_comparision(const char *s_1, const char *s_2)
{
    unsigned int i=0, size=string_length(s_1);

    if(size!=string_length(s_2)) return 0;
    else
    {
        while(s_1[i])
        {
            if(s_1[i]!=s_2[i])
                return 0;
            i++;
        }
    }

    return 1;
}

GLuint string_length(const char *s)
{
    GLuint tmp=0;
    while(s[tmp]!='\0') tmp++;
    return tmp;
}

GLubyte memory_comparision(const GLubyte *m1, const GLubyte *m2, GLuint size)
{
    GLuint i=0;

    for(i=0; i<size; i++)
        if(m1[i]!=m2[i]) return 0;

    return 1;
}
