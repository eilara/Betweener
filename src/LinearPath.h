
#ifndef LINEARPATH_H
#define LINEARPATH_H

#include "Vector.h"
#include "IPath.h"

class LinearPath : public IPath{

    public:
        LinearPath(Vector<int,2> from, Vector<int,2> to);
        Vector<int,2> solve(float t);
    private:
        Vector<int,2> from, to, diff;

};

#endif
