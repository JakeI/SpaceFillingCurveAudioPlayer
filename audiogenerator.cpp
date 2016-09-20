#include "audiogenerator.h"

AudioGenerator::AudioGenerator() : QObject()
{
}

AudioGenerator::~AudioGenerator(){

}

void AudioGenerator::start(QObject *parent){

    format = new QAudioFormat();
    format->setChannelCount(1);
    format->setSampleRate(44100);
    format->setCodec("audio/pcm");
    format->setSampleSize(8);
    format->setByteOrder(QAudioFormat::LittleEndian);
    format->setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if(!info.isFormatSupported(*format)){
        cout << "Format is not supported" << endl;
    }else{
        cout << "Format is supported" << endl;
    }

    audio = new QAudioOutput(*format, this);
    audio->setObjectName("My Audio Obj");

    device = new AudioDivice();
    audio->start(device);
}
