#include "hemoltoncurve.h"

template <typename T>
HemoltonCurve::Point<T>::Point(T x, T y){
    this->x = x;
    this->y = y;
}

template <typename T>
HemoltonCurve::Point<T>::Point(){
    this->x = -1;
    this->y = -1;
}

template <typename T>
HemoltonCurve::Point<T>::set(T x, T y){
    this->x = x;
    this->y = y;
}


HemoltonCurve::Array2D::Array2D(){
    data = nullptr;
}

HemoltonCurve::Array2D::~Array2D(){
    if(data != nullptr)
        delete[] data;
}

void HemoltonCurve::Array2D::formIndex(Point<int> *i, int w, int h){
    this->w = w;
    this->h = h;
    this->len = w*h;
    data = new int[len];

    for(int j = 0; j < len; j++){
        set(i[j].x, i[j].y, j);
    }
}

void HemoltonCurve::Array2D::set(int x, int y, int value){
    int i = x + y*w;
    if(i > 0 && i < len){
        data[i] = value;
    }
}

int HemoltonCurve::Array2D::get(int x, int y){
    int i = x + y*w;
    if(i > 0 && i < len){
        return data[i];
    }
    return -1;
}


void HemoltonCurve::calcCurve(){
    hilbert(0, 0, dim, 0, 0, dim, log(dim)/log(2));
    inverse.formIndex(i, dim, dim);

    //for(int j = 0; j < 100; j++)
    //    cout << "Point = (" << i[j].x << ", " << i[j].y << ")" << endl;
}

void HemoltonCurve::add(int x, int y){
    static int pointIndex = 0;
    this->i[pointIndex++].set(x, y);
}

void HemoltonCurve::hilbert(int x, int y, int xi, int xj, int yi, int yj, int n){
    if(n <= 0){
        add(x+(xi+yi)/2, y+(xj+yj)/2);
    }else{
        hilbert(x, y, yi/2, yj/2, xi/2, xj/2, n-1);
        hilbert(x+xi/2, y+xj/2, xi/2, xj/2, yi/2, yj/2, n-1);
        hilbert(x+xi/2+yi/2, y+xj/2+yj/2, xi/2, xj/2, yi/2, yj/2, n-1);
        hilbert(x+xi/2+yi, y+xj/2+yj, -yi/2, -yj/2, -xi/2, -xj/2, n-1);
    }
}


HemoltonCurve::HemoltonCurve(int dimention){
    dim = dimention;
    len = dim*dim;
    i = new Pointi[len];
    calcCurve();
}

HemoltonCurve::~HemoltonCurve(){
    delete[] i;
}


int HemoltonCurve::get(int X, int Y){
    return inverse.get(X, Y);
}

HemoltonCurve::Pointi HemoltonCurve::get(int I){
    if(I > 0 && I < len){
        return i[I];
    }
    Pointi p(-1, -1);
    return p;
}


float HemoltonCurve::get(float X, float Y){
    return (float)get(X*(float)dim, Y*(float)dim)/(float)len;
}

HemoltonCurve::Pointf HemoltonCurve::get(float I){
    Pointi p = get((int)floorf(I*len));
    Pointf q((float)p.x/(float)dim, (float)p.y/(float)dim);
    return q;
}
