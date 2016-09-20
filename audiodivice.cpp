#include "audiodivice.h"


AudioDivice::Note AudioDivice::music[] = {
    { NOTE_c, 250 }, { NOTE_e, 125 }, { NOTE_f, 125 },
    { NOTE_c, 500 }, { NOTE_b, 250 }, { NOTE_dp, 250 },
    { NOTE_pause, 1000 }
};

AudioDivice::AudioDivice() : QIODevice(), currentSample(0)
{
    if(!open(QIODevice::ReadOnly)){
        cout << "Could not open the AudioDevice" << endl;
    }
}

inline float AudioDivice::linearInterplolation(float a, float b, float mix){
    return a*mix + b*(1.0f-mix);
}

inline float AudioDivice::cosineInterploation(float a, float b, float mix){
    return linearInterplolation(a, b, -cos(M_PI*mix)/2.0f+0.5f);
}


inline float AudioDivice::poly(float x, float* coeff, int dim){ //f(x) = coeff[0]*x^dim + coeff[1]*x^(dim-1)+...+coeff[dim-1]
    if(dim <= 0)
        return 0;
    float f = coeff[0];
    int end = dim-2;
    for(int i = 0; i < dim-2; i++){
        f = f*x+coeff[i+1];
    }
    return f;
}

void AudioDivice::getInterPoly(const float f0, const float m0, const float f1, const float m1, float* coeff){
    coeff[0] = m1+m0-2.0f*f1+2.0f*f0;
    coeff[1] = 3.0f*f1-m1-2.0f*m0-3.0f*f0;
    coeff[2] = m0;
    coeff[3] = f0;
    return;
}

#define interpolate cosineInterploation

qint64 AudioDivice::readData(char *data, qint64 maxSize){

    int musicLength_s = 0, noteCount = sizeof(music)/sizeof(Note);
    for(int i = 0; i < noteCount; i++){
        musicLength_s += music[i].getLenSamples(44100);
    }

    float factor = 2*M_PI/44100;

    static int noteId = -1, nextNoteId = 0, noteStart = 0, noteEnd = 0, noteLen = 1;
    static float coeff[4] = { 0.0f };

    int end = currentSample + maxSize;
    int j = 0;
    for(int i = currentSample; i < end; i++){

       int s = i % musicLength_s;

       if(s >= noteEnd){
           noteId = ++noteId % noteCount;
           nextNoteId = ++nextNoteId % noteCount;
           noteStart = s;
           noteEnd += (float)music[noteId].lenMS*0.001f*44100.0f;
           noteLen = noteEnd - s;
           getInterPoly(music[noteId].freq,
                 2.0f*(music[nextNoteId].freq+music[(noteId-1)%noteCount].freq)/2.0f,
                 music[nextNoteId].freq,
                 2.0f*(music[noteId].freq+music[(nextNoteId+1)&noteCount].freq)/2.0f,
                 coeff);
       }

       //float alpha = factor*music[noteId].freq*i;
       //float alpha = factor*i*interpolate(music[noteId].freq, music[nextNoteId].freq,
       //                           (s-noteStart)/noteLen);
       float alpha = factor*i*poly((s-noteStart)/noteLen, coeff, 4);

       unsigned char c = (unsigned char) (32/2)*
                (sinf(alpha)+sinf(5*alpha))+32u;
        data[j++] = (char)c;
        currentSample++;
    }
    return maxSize;
}
