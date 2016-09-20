#ifndef HEMOLTONCURVE_H
#define HEMOLTONCURVE_H

#include <math.h>

#include <iostream>
using namespace std;

class HemoltonCurve
{
public:

    template <typename T>
    struct Point{
        T x, y;
        Point(T x, T y);
        Point();
        set(T x, T y);
    };

    typedef Point<int> Pointi;
    typedef Point<float> Pointf;

private:

    int dim;
    int len;

    class Array2D{
    private:
        int h, w, len;
        int *data;

        void set(int x, int y, int value);

    public:
        Array2D();
        ~Array2D();
        void formIndex(Point<int> *i, int w, int h);
        int get(int x, int y);
    };

    Array2D inverse;
    Pointi *i;

    void calcCurve();
    void add(int x, int y);
    void hilbert(int x, int y, int xi, int xj, int yi, int yj, int n);

public:
    HemoltonCurve(int dimention);
    ~HemoltonCurve();

    int get(int X, int Y);
    Pointi get(int I);

    float get(float X, float Y);
    Pointf get(float I);

};

#endif // HEMOLTONCURVE_H
