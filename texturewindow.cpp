#include "texturewindow.h"

TextureWindow::TextureWindow()
    : shader(0), vao(0), totalIndecies(0), mousePosLocation(0)
{
    frameCounter = 0; //Just to Check if its working
}

void TextureWindow::initShader(){

    shader = new QOpenGLShaderProgram(this);
    shader->addShaderFromSourceFile(QOpenGLShader::Vertex,
                "C:/A/B_Dokumente/Dokumente/AudioPlayer/img.vertex");
    shader->addShaderFromSourceFile(QOpenGLShader::Fragment,
                "C:/A/B_Dokumente/Dokumente/AudioPlayer/img.fragment");
    shader->link();

    matrixLocation = shader->uniformLocation("matrix");
    projMatrixLocation = shader->uniformLocation("proj");
    mousePosLocation = shader->uniformLocation("mousePos");

    img = new QImage("C:/A/H_Desktop/Deskop/Textures/RendomPlasma.png");
    texture = new QOpenGLTexture(img->mirrored());
}

void TextureWindow::initialize(){

    initShader();

    hemolton = new HemoltonCurve(img->width()); // Just Experimentaly

    int w = img->width()/256, h = img->height()/256;

    float *v;
    int len = GLHelper::generate11GridData2D(w, h, v);

    unsigned int *e;
    totalIndecies = GLHelper::generateGridIndex2D(w, h, e);

    //unsigned int *ee = GLHelper::trianglesToWires(e, totalIndecies);
    //totalIndecies *= 2;

    shader->bind();

    vao = new QOpenGLVertexArrayObject(this);
    vao->create();
    vao->bind();

    QOpenGLBuffer vbo;
    GLHelper::toVBO(&vbo, v, len, 2);
    GLHelper::toAttribute(shader, 0, 2);
    GLHelper::toAttribute(shader, 1, 2);
    vbo.release();

    QOpenGLBuffer ebo;
    GLHelper::toEBO(&ebo, e, totalIndecies);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.bufferId());
    ebo.release();

    vao->release();
    shader->release();

    delete[] v;
    delete[] e;
    //delete[] ee;


    generator = new AudioGenerator();
    generator->start(this);

}

void TextureWindow::render(){
    const qreal retinaScale = devicePixelRatio();
    int w = width(), h = height();
    glViewport(0, 0, w*retinaScale, h*retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

    shader->bind();

    QMatrix4x4 proj;
    proj.setToIdentity();
    float aspect = (float) w/ (float)h;
    //proj.ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);

    float a = ((float)h/(float)w)*((float)img->height()/(float)img->width());
    proj.translate(-a, -1.0f, 0.0f);
    proj.scale(2.0f*a, 2.0f, 0.0f);

    QMatrix4x4 m;
    m = proj;


    shader->setUniformValue(matrixLocation, m);
    shader->setUniformValue(projMatrixLocation, proj);

    //int d = (w-img->width()*h/img->height())/2;
    //int Wprim = img->width()*h/img->height();
    //QVector4D mousepos((float)(mouseCoords.x-d)/Wprim,
    //                   1.0f-(float)mouseCoords.y/h,
    //                   0.0f, 1.0f);
    HemoltonCurve::Pointf p = hemolton->get((float)frameCounter/10000.0f /*1048576.0f*/);
    QVector4D mousepos(p.x, p.y, 0.0f, 1.0f);
    //mousepos = m*mousepos;

    shader->setUniformValue(mousePosLocation, mousepos);

    vao->bind();
    texture->bind();
    glDrawElements(GL_TRIANGLES, totalIndecies-(3*experimentalParam),
                   GL_UNSIGNED_INT, (void*)0);
    vao->release();

    shader->release();

    ++frameCounter;

}
