#include <assert.h>
#include "particle.h"

void Particle::integrate(real duration)
{
    assert(duration > 0.0);
    position.add_scaled_vector(velocity, duration);//update linear position
    Vector3D resulting_acceleration = acceleration;
    resulting_acceleration.add_scaled_vector(accumulated_force, inverse_mass);//workout acceleration from the force
    velocity.add_scaled_vector(resulting_acceleration, duration);//update linear velocity
    velocity *= real_pow(damping, duration);

}
