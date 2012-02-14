
#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <algorithm>
#include <iostream>

template<typename T,int DIM>
class Vector {

    public:
        T arr[DIM];

        static int size () { return DIM; }

              T& operator[] (int i)       { return arr[i]; }
        const T& operator[] (int i) const { return arr[i]; }

        Vector<T,DIM>& operator= (const Vector<T,DIM>& rhs) {
            std::copy(rhs.arr,rhs.arr + DIM, arr);
            return *this;
        }

};

template<typename T,int DIM>
bool operator== (const Vector<T,DIM>& lhs, const Vector<T,DIM>& rhs)
    { return std::equal(lhs.arr, lhs.arr + DIM, rhs.arr); }

template<typename T,int DIM>
bool operator!= (const Vector<T,DIM>& lhs, const Vector<T,DIM>& rhs) {
    for (unsigned i=0; i<DIM; ++i) { if (lhs[i] != rhs[i]) return true; }
    return false;
}

template<typename T,int DIM>
Vector<T,DIM> operator+ (const Vector<T,DIM>& lhs, const Vector<T,DIM>& rhs) {
    Vector<T,DIM> res;
    for (unsigned i=0; i<DIM; ++i) { res[i] = lhs[i] + rhs[i]; }
    return res;
}

template<typename T,int DIM>
Vector<T,DIM> operator- (const Vector<T,DIM>& lhs, const Vector<T,DIM>& rhs) {
    Vector<T,DIM> res;
    for (unsigned i=0; i<DIM; ++i) { res[i] = lhs[i] - rhs[i]; }
    return res;
}

template<typename T,int DIM>
Vector<T,DIM> operator* (const Vector<T,DIM>& t, float k) {
    Vector<T,DIM> res;
    for (unsigned i=0; i<DIM; ++i) { res[i] = t[i] * k; }
    return res;
}

template<typename T,int DIM>
Vector<T,DIM> operator/ (const Vector<T,DIM>& t, float k) {
    Vector<T,DIM> res;
    for (unsigned i=0; i<DIM; ++i) { res[i] = t[i] / k; }
    return res;
}

template<typename T,int DIM>
std::ostream& operator<< (std::ostream& os, const Vector<T,DIM>& t)
{
    os << "{" << t[0];
    for (unsigned i=1; i<DIM; ++i) { os << "," << t[i]; }
    os << "}";
    return os;
}

#endif
