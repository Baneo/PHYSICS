#include "point3d.h"

real Point3D::getX() const
{
    return x;
}

real Point3D::getY() const
{
    return y;
}

real Point3D::getZ() const
{
    return z;
}

Point3D::Point3D()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    std::cout << "Point created by default\n" ;
}

Point3D::Point3D(real x, real y, real z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    std::cout << "Point created\n";
}


