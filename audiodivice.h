#ifndef AUDIODIVICE_H
#define AUDIODIVICE_H

#include <QIODevice>

#include <iostream>
using namespace std;

#define NOTE_c  130.813f
#define NOTE_e  164.814f
#define NOTE_f  174.614f
#define NOTE_b  246.942f
#define NOTE_dp  293.665f
#define NOTE_pause 0.0f


class AudioDivice : public QIODevice
{
public:
    AudioDivice();

    qint64 readData(char *data, qint64 maxSize);
    qint64 writeData(const char *data, qint64 len){ return -1; }

private:

    struct Note{
        float freq;
        int lenMS;
        inline int getLenSamples(int sampleRate){
            return lenMS*sampleRate*1000;
        }
    };

    static Note music[7];

    int currentSample;



    inline float linearInterplolation(float a, float b, float mix);
    inline float cosineInterploation(float a, float b, float mix);
    inline float poly(float x, float* coeff, int dim);
    void getInterPoly(const float f0, const float m0, const float f1, const float m1, float* coeff);

};

#endif // AUDIODIVICE_H
