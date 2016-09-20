#include "mainwindow.h"
#include "texturewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);

    TextureWindow w;
    w.setFormat(format);
    w.resize(640, 480);
    w.show();
    w.setAnimating(true);

    return app.exec();
}
