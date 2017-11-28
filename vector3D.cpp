#include "vector3D.h"
#include "stdio.h"
#include "iostream"


real Vector3D::setX(real a)
{
    x = a;
}

real Vector3D::setY(real a)
{
    y = a;
}

real Vector3D::setZ(real a)
{
    z = a;
}


real Vector3D::getX() const
{
    return x;
}

real Vector3D::getY() const
{
    return y;
}

real Vector3D::getZ() const
{
    return z;
}

Vector3D::Vector3D()
{
    x = 0;
    y = 0;
    z = 0;
    std::cout << "Vector created by default\n";
}

Vector3D::Vector3D(real x, real y, real z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    std::cout << "Vector created\n";
}

void Vector3D::invert()
{
    x = -x;
    y = -y;
    z = -z;
}
void Vector3D::print()
{
    std::cout << "x = " << x << "; y = " << y << "; z = " << z << "\n";
}

void Vector3D::add(Vector3D *vect)
{
    x += vect->x;
    y += vect->y;
    z += vect->z;

}

void Vector3D::sub(Vector3D *vect)
{
    x -= vect->x;
    y -= vect->y;
    z -= vect->z;

}

real Vector3D::magnitude() const
{
    return real_sqrt(x*x+y*y+z*z);
}

void Vector3D::normalize()
{
    real n = magnitude();
    if (n > 0)
    {
        (*this)*=((real)1)/n;
    }
}

Vector3D Vector3D::unit() const
{
    Vector3D result = *this;
    result.normalize();
    return result;
}

real Vector3D::square_magnitude()
{
    return x*x+y*y+z*z;
}

void Vector3D::operator*=(const real value)
{
    x *= value;
    y *= value;
    z *= value;
}

Vector3D Vector3D::operator*(const real value) const
{
    return Vector3D(x*value, y* value, z*value);
}

real Vector3D::scalar_product(Vector3D *vect)
{
    return vect->x * x + vect->y * y + vect->z * z;
}

bool Vector3D::isEqual(Vector3D *vect)
{
    return vect->x==x && vect->y==y && vect->z==z;
}

void Vector3D::operator+=(const Vector3D& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
}

Vector3D Vector3D::operator+(const Vector3D& v)const
{
    return Vector3D(x+v.x,y+v.y,z+v.z);
}

void Vector3D::operator-=(const Vector3D& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

Vector3D Vector3D::operator-(const Vector3D& v)const
{
    return Vector3D(x-v.x,y-v.y,z-v.z);
}

void Vector3D::add_scaled_vector(const Vector3D& v, real scale)
{
    x += v.x * scale;
    y += v.y * scale;
    z += v.z * scale;
}

Vector3D Vector3D::component_product(const Vector3D& v) const
{
    return Vector3D(x+v.x, y+v.y, z+v.z);
}

void Vector3D::component_product_update(const Vector3D& v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
}

real Vector3D::operator*(const Vector3D& v)
{
    return x*v.x+y*v.y+z*v.z;
}

Vector3D Vector3D::vector_product(const Vector3D& v) const
{
    return Vector3D(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
}

void Vector3D::operator %=(const Vector3D& v)
{
    *this = vector_product(v);
}
Vector3D Vector3D::operator%(const Vector3D& v) const
{
    return Vector3D(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
}


real Vector3D::operator[](unsigned i) const
{
    if (i == 0) return x;
    if (i == 1) return y;
    return z;
}

real& Vector3D::operator[](unsigned i)
{
    if (i == 0) return x;
    if (i == 1) return y;
    return z;
}

void Vector3D::trim(real limit)
{
    if(square_magnitude() > limit*limit)
    {
        normalize();
        x *= limit;
        y *= limit;
        z *= limit;
    }
}

bool Vector3D::operator==(const Vector3D& vect) const
{
    return x == vect.getX() && y == vect.getY() && z == vect.getZ();
}

bool Vector3D::operator!=(const Vector3D& vect)const
{
    return !(*this == vect);
}
bool Vector3D::operator<(const Vector3D& vect) const
{
    return x < vect.getX() && y < vect.getY() && z < vect.getZ();
}

bool Vector3D::operator>(const Vector3D& vect) const
{
    return x > vect.getX() && y > vect.getY() && z > vect.getZ();
}

bool Vector3D::operator<=(const Vector3D& vect) const
{
    return x <= vect.getX() && y <= vect.getY() && z <= vect.getZ();
}

bool Vector3D::operator>=(const Vector3D& vect) const
{
    return x >= vect.getX() && y >= vect.getY() && z >= vect.getZ();
}

void Vector3D::clear()
{
    x = y = z = 0;
}






