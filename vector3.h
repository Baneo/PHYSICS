#ifndef VECTOR3_H
#define VECTOR3_H


class Vector3
{
public:
    float x;
    float y;
    float z;
    Vector3();
    Vector3(const float x, const float y, const float z);
    void invert();
    void print();
    void add(Vector3*);
    void sub(Vector3*);
    void normalize();
    float magnitude();
    float square_magnitude();
    void operator*=(const float value);
    Vector3 operator*(const float value) const;
};

#endif // VECTOR3_H
