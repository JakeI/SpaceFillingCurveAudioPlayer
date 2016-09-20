#ifndef TEXTUREWINDOW_H
#define TEXTUREWINDOW_H

#include <QtMultimedia/QAudioOutput>
#include <QtMultimedia/QAudioFormat>

#include "glwindow.h"
#include "glhelper.h"
#include "audiogenerator.h"

#include "hemoltoncurve.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGlShaderProgram>
#include <QtGui/QOpenGLTexture>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLVertexArrayObject>
#include <QtGui/QScreen>

//#include <QtCore/qmat.h>

class TextureWindow : public GLWindow
{
public:
    TextureWindow();

    void initialize() Q_DECL_OVERRIDE;
    void render() Q_DECL_OVERRIDE;

private:

    void initShader();


    GLuint matrixLocation, projMatrixLocation, mousePosLocation;

    QOpenGLTexture *texture;
    QOpenGLVertexArrayObject *vao; int totalIndecies;

    QOpenGLShaderProgram *shader;

    int frameCounter;

    QImage *img;

    AudioGenerator *generator;

    HemoltonCurve *hemolton;
};

#endif // TEXTUREWINDOW_H
