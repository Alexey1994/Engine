#ifndef OGL_MATH_H_INCLUDED
#define OGL_MATH_H_INCLUDED

#include <GL/gl.h>

typedef GLfloat Vector4[4];
typedef GLfloat Vector[3];
typedef GLfloat Point[3];

#define	PI	3.14159265358979323846

#define DegToRad(a) (((a)*PI)/180.0f)
#define RadToDeg(a) (((a)*180.0f)/PI)

#define VectorCopy(a,b)         ((a)[0]=(b)[0],(a)[1]=(b)[1],(a)[2]=(b)[2])
#define VectorScalarProduct(x,y)((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])
#define VectorSubtract(a,b,c)	((c)[0]=(a)[0]-(b)[0],(c)[1]=(a)[1]-(b)[1],(c)[2]=(a)[2]-(b)[2])
#define VectorAdd(a,b,c)		((c)[0]=(a)[0]+(b)[0],(c)[1]=(a)[1]+(b)[1],(c)[2]=(a)[2]+(b)[2])

#define VectorClear(a)			((a)[0]=(a)[1]=(a)[2]=0)
#define VectorNegate(a,b)		((b)[0]=-(a)[0],(b)[1]=-(a)[1],(b)[2]=-(a)[2])
#define VectorSet(v, x, y, z)	((v)[0]=(x), (v)[1]=(y), (v)[2]=(z))

#define PointToVector(p1,p2,v)  ((v)[0]=(p2)[0]-(p1)[0],(v)[1]=(p2)[1]-(p1)[1],(v)[2]=(p2)[2]-(p1)[2])

void VectorOrtogonalize(const Vector a, const Vector b, Vector normale);
void VectorNormalize(Vector a);

GLfloat power_10(int n);
GLuint char_to_GLuint(char *s);
GLint char_to_GLint(char *s);
GLfloat char_to_GLfloat(char *s);

GLubyte string_comparision(const char *s_1, const char *s_2);
GLuint string_length(const char *s);
void string_copy(char *s1, const char *s2);

GLubyte memory_comparision(const GLubyte *m1, const GLubyte *m2, GLuint size);

#endif
