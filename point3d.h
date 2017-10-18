#ifndef POINT3D_H
#define POINT3D_H

#include <iostream>


class Point3D
{
private:
    float x;
    float y;
    float z;

public:
    Point3D();
    Point3D(const float x, const float y, const float z);
    float getX() const;
    float getY() const;
    float getZ() const;
};

#endif // POINT3D_H
