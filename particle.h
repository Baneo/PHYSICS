#ifndef PARTICLE_H
#define PARTICLE_H

#include "vector3D.h"


class Particle
{
public:
    Vector3D position; //linear position of particle in world space
    Vector3D velocity; //linear velocity of particle in world space
    Vector3D acceleration; //acceleration of particle (mainly gravity)
    Vector3D accumulated_force; //force to be applied at next iteration
    real damping;
    real inverse_mass; //inverse mass of the particle, integration simpler and more useful, beter to have infinite mass than zero mass

    void integrate(real duration);
    
    void setPosition(const Vector3D &position);
    void setPosition(const real x, const real y, const real z);

    void getPosition(Vector3D *position)const;
    Vector3D getPosition()const;

    void setVelocity(const Vector3D &velocity);
    void setVelocity(const real x, const real y, const real z);

    void getVelocity(Vector3D *position)const;
    Vector3D getVelocity()const;

    void setMass(const real mass);
	real getMass()const;

	void setDamping(const real damping);
	real getDamping()const;

	void setAcceleration(const Vector3D &acceleration);
	void setAcceleration(const real x, const real y, const real z);

	void getAcceleration(Vector3D *acceleration)const;
    Vector3D getAcceleration()const;

    void clearAccumulator();

};

#endif // PARTICLE_H
