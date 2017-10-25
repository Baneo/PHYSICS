#ifndef POINT3D_H
#define POINT3D_H

#include <iostream>
#include "precision.h"

class Point3D
{
private:
    real x;
    real y;
    real z;

public:
    Point3D();
    Point3D(const real x, const real y, const real z);
    real getX() const;
    real getY() const;
    real getZ() const;
};

#endif // POINT3D_H
