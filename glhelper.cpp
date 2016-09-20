#include "glhelper.h"


unsigned int* GLHelper::trianglesToWires(unsigned int *triangles, int length){
    if(length%3 != 0)
        return nullptr;
    int l = length / 3;

    unsigned int *res = new unsigned int[2*length];
    int k = 0;

    for(int i = 0; i < l; i++){
        int j = i * 3;

        res[k++] = triangles[j];
        res[k++] = triangles[j+1];
        res[k++] = triangles[j+1];
        res[k++] = triangles[j+2];
        res[k++] = triangles[j+2];
        res[k++] = triangles[j];
    }

    return res;
}

int GLHelper::generate11GridData2D(int w, int h, float* &vertecies){

    int xlen = w+1, ylen = h+1;
    int length = xlen*ylen;
    vertecies = new float[2*length];

    float yStride = 1.0f/(ylen-1), xStride = 1.0f/(xlen-1);
    int iv = 0;

    for(int y = 0; y < ylen; y++){
        float fy = y*yStride;
        for(int x = 0; x < xlen; x++){
            vertecies[iv++] = x*xStride;
            vertecies[iv++] = fy;
        }
    }

    return length;
}

int GLHelper::generateGridIndex2D(int w, int h, unsigned int* &indecies){
    int count = w*h*6;
    int xlen = w+1;
    indecies = new unsigned int[count];
    int ie = 0;
    for(int j = 0; j < h; j++){
        for(int i = 0; i < w; i++){
            int a = j*xlen+i;
            int b = a+1;
            int c = a+xlen;
            indecies[ie++] = a;
            indecies[ie++] = c;
            indecies[ie++] = b;
            indecies[ie++] = b;
            indecies[ie++] = c;
            indecies[ie++] = c+1;
        }
    }
    return count;
}

void GLHelper::toVBO(QOpenGLBuffer *vbo, float *vertecies, int countVertex, int dim){
    vbo->create();
    vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo->bind();
    vbo->allocate(vertecies, countVertex*dim*sizeof(float));
}

void GLHelper::toAttribute(QOpenGLShaderProgram *shader,
                int attrib, int dim){
    shader->enableAttributeArray(attrib);
    shader->setAttributeArray(attrib, GL_FLOAT, 0, dim);
}

void GLHelper::toEBO(QOpenGLBuffer *ebo, unsigned int *indices, int countIndecies){
    ebo->create();
    ebo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    ebo->bind();
    ebo->allocate(indices, countIndecies*sizeof(unsigned int));
}



