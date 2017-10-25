#ifndef PARTICLE_H
#define PARTICLE_H

#include "vector3D.h"


class Particle
{
public:
    Vector3D position; //linear position of particle in world space
    Vector3D velocity; //linear velocity of particle in world space
    Vector3D acceleration; //acceleration of particle (mainly gravity)

    real damping;
    real inverse_mass; //inverse mass of the particle, integration simpler and more useful, beter to have infinite mass than zero mass

    void integrate(real duration);
};

#endif // PARTICLE_H
