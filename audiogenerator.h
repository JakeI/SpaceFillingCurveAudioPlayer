#ifndef AUDIOGENERATOR_H
#define AUDIOGENERATOR_H

#include <QObject>

#include <QTimer>

#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioOutput>

#include "audiodivice.h"

#include <iostream>
using namespace std;

class AudioGenerator : QObject
{
private:
    Q_OBJECT

public:
    AudioGenerator();
    ~AudioGenerator();

    void start(QObject *parent = NULL);

public slots:

protected:

private:

    QAudioOutput *audio;
    QAudioFormat *format;

    AudioDivice *device;
};

#endif // AUDIOGENERATOR_H
