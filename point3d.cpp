#include "point3d.h"

float Point3D::getX() const
{
    return x;
}

float Point3D::getY() const
{
    return y;
}

float Point3D::getZ() const
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

Point3D::Point3D(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    std::cout << "Point created\n";
}


