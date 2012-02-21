
#ifndef IPATH_H
#define IPATH_H

#include "Vector.h"

class IPath {

    public:
        virtual ~IPath() {}
        virtual Vector<int,2> solve(float t) = 0;

};

#endif
