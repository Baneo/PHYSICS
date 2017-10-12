#include "vector3.h"
#include "stdio.h"
#include "iostream"
#include "math.h"


using namespace std;

Vector3::Vector3()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    cout << "Vector created by default\n";
}

Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    cout << "Vector created\n";
}

void Vector3::invert()
{
    this->x = -x;
    this->y = -y;
    this->z = -z;
}
void Vector3::print()
{
    std::cout << "x = " << this->x << "; y = " << this->y << "; z = " << this->z << "\n";
}

void Vector3::add(Vector3 *vect)
{
    this->x += vect->x;
    this->y += vect->y;
    this->z += vect->z;

}

void Vector3::sub(Vector3 *vect)
{
    this->x -= vect->x;
    this->y -= vect->y;
    this->z -= vect->z;

}

void Vector3::normalize()
{
    float n = magnitude();
    if (n > 0)
    {
        (*this)*=((float)1/n);
    }
}

float Vector3::magnitude()
{
    return sqrtf(x*x+y*y+z*z);
}

float Vector3::square_magnitude()
{
    return x*x+y*y+z*z;
}

void Vector3::operator*=(const float value)
{
    this->x *= value;
    this->y *= value;
    this->z *= value;
}

Vector3 Vector3::operator*(const float value) const
{
    return Vector3(x*value, y* value, z*value);
}

