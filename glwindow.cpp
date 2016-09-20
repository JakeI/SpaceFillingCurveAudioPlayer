#include "glwindow.h"


GLWindow::GLWindow(QWindow *parent)
    : QWindow(parent)
    , m_update_pending(false)
    , m_animating(false)
    , m_context(0)
    , m_device(0)
    , mouseCoords()
{
    setSurfaceType(QWindow::OpenGLSurface);

    experimentalParam = 0;
}


GLWindow::~GLWindow()
{
    delete m_device;
}

void GLWindow::render(QPainter *painter)
{
    Q_UNUSED(painter);
}

void GLWindow::initialize()
{
}

void GLWindow::render()
{
    if (!m_device)
        m_device = new QOpenGLPaintDevice;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    m_device->setSize(size());

    QPainter painter(m_device);
    render(&painter);
}

void GLWindow::renderLater()
{
    if (!m_update_pending) {
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

bool GLWindow::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::UpdateRequest:
        m_update_pending = false;
        renderNow();
        return true;
    default:
        return QWindow::event(event);
    }
}

void GLWindow::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Plus:
        experimentalParam += 1;
        break;
    case Qt::Key_Minus:
        experimentalParam -= 1;
        break;
    }
    return QWindow::keyPressEvent(event);
}

void GLWindow::mouseMoveEvent(QMouseEvent *event){
    mouseCoords.x = event->x();
    mouseCoords.y = event->y();
    //cout << "New mouse coords (x, y) = (" << mouseCoords.x <<
    //        ", " << mouseCoords.y << ")" << endl;
}

void GLWindow::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);

    if (isExposed())
        renderNow();
}

void GLWindow::renderNow()
{
    if (!isExposed())
        return;

    bool needsInitialize = false;

    if (!m_context) {
        m_context = new QOpenGLContext(this);
        m_context->setFormat(requestedFormat());
        m_context->create();

        needsInitialize = true;
    }

    m_context->makeCurrent(this);

    if (needsInitialize) {
        initializeOpenGLFunctions();
        initialize();
    }

    render();

    m_context->swapBuffers(this);

    if (m_animating)
        renderLater();
}

void GLWindow::setAnimating(bool animating)
{
    m_animating = animating;

    if (animating)
        renderLater();
}
