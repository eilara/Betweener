
#include "LinearPath.h"

LinearPath::LinearPath(Vector<int,2> from, Vector<int,2> to) :
    from(from), to(to), diff(to - from) {}

Vector<int,2> LinearPath::solve(float t) {
    return from + diff * t;
}


