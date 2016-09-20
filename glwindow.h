#ifndef GLWINDOW_H
#define GLWINDOW_H


#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QKeyEvent>
#include <QtGui/QMouseEvent>

#include <QtCore/QCoreApplication>

#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>

#include <iostream>
using namespace std;

class GLWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GLWindow(QWindow *parent = 0);
    ~GLWindow();

    virtual void render(QPainter *painter);
    virtual void render();

    virtual void initialize();

    void setAnimating(bool animating);

public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;

    void exposeEvent(QExposeEvent *event) Q_DECL_OVERRIDE;

    void keyPressEvent(QKeyEvent * event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    struct Point{
        int x, y;
        Point(){ x = 0; y = 0; }
    }mouseCoords;

    int experimentalParam;

private:
    bool m_update_pending;
    bool m_animating;

    QOpenGLContext *m_context;
    QOpenGLPaintDevice *m_device;
};
#endif // GLWINDOW_H
