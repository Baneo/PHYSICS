#include "vector3D.h"
#include "stdio.h"
#include "iostream"
#include "math.h"


float Vector3D::getX() const
{
    return x;
}

float Vector3D::getY() const
{
    return y;
}

float Vector3D::getZ() const
{
    return z;
}

Vector3D::Vector3D()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    std::cout << "Vector created by default\n";
}

Vector3D::Vector3D(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    std::cout << "Vector created\n";
}

void Vector3D::invert()
{
    this->x = -x;
    this->y = -y;
    this->z = -z;
}
void Vector3D::print()
{
    std::cout << "x = " << this->x << "; y = " << this->y << "; z = " << this->z << "\n";
}

void Vector3D::add(Vector3D *vect)
{
    this->x += vect->x;
    this->y += vect->y;
    this->z += vect->z;

}

void Vector3D::sub(Vector3D *vect)
{
    this->x -= vect->x;
    this->y -= vect->y;
    this->z -= vect->z;

}

void Vector3D::normalize()
{
    float n = magnitude();
    if (n > 0)
    {
        (*this)*=((float)1/n);
    }
}

float Vector3D::magnitude()
{
    return sqrtf(x*x+y*y+z*z);
}

float Vector3D::square_magnitude()
{
    return x*x+y*y+z*z;
}

void Vector3D::operator*=(const float value)
{
    this->x *= value;
    this->y *= value;
    this->z *= value;
}

Vector3D Vector3D::operator*(const float value) const
{
    return Vector3D(x*value, y* value, z*value);
}

float Vector3D::scalar_product(Vector3D *vect)
{
    return 0;
}
