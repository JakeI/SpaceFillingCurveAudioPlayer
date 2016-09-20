#ifndef GLHELPER_H
#define GLHELPER_H

#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLShaderProgram>

class GLHelper
{
public:
    static unsigned int* trianglesToWires(unsigned int *triangles, int length);
    static int generate11GridData2D(int w, int h, float* &vertecies);
    static int generateGridIndex2D(int w, int h, unsigned int* &indecies);
    static void toVBO(QOpenGLBuffer *vbo, float *vertecies,
                      int countVertex, int dim);
    static void toAttribute(QOpenGLShaderProgram *shader,
                            int attrib, int dim);
    static void toEBO(QOpenGLBuffer *ebo, unsigned int *indices,
                      int countIndecies);
};

#endif // GLHELPER_H
