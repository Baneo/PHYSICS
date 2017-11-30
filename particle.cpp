#include <assert.h>
#include "inc.h"

void Particle::integrate(real duration)
{
    assert(duration > 0.0);
    position.add_scaled_vector(velocity, duration);//update linear position
    Vector3D resulting_acceleration = acceleration;
    resulting_acceleration.add_scaled_vector(accumulated_force, inverse_mass);//workout acceleration from the force
    velocity.add_scaled_vector(resulting_acceleration, duration);//update linear velocity
    velocity *= real_pow(damping, duration);

}

    void Particle::setPosition(const Vector3D &position){
    	this->position = position;
    }
    void Particle::setPosition(const real x, const real y, const real z){
    	this->position.setX(x);this->position.setY(y);this->position.setZ(z);
    }

    void Particle::getPosition(Vector3D *position)const{
    	*position = this->position;
    }

    Vector3D Particle::getPosition()const{
    	return position;
    }


    void Particle::setVelocity(const Vector3D &velocity){
    	this->velocity = velocity;
    }
    void Particle::setVelocity(const real x, const real y, const real z){
    	this->velocity.setX(x);this->velocity.setY(y);this->velocity.setZ(z);
    }

    void Particle::getVelocity(Vector3D *velocity)const{
    	*velocity = this->velocity;
    }

    Vector3D Particle::getVelocity()const{
    	return velocity;
    }

    void Particle::setMass(const real mass){
    	assert(mass!=0);
    	this->inverse_mass = (real(1.0)/mass);
    }
	real Particle::getMass()const{
		if (inverse_mass == 0) {
			return DBL_MAX;
		} else {
			return (real(1.0)/inverse_mass);
		}
	}

	void Particle::setDamping(const real damping){
		this->damping = damping;
	}

	real Particle::getDamping()const{
		return damping;
	}

	void Particle::setAcceleration(const Vector3D &acceleration){
		this->acceleration = acceleration;
	}
	void Particle::setAcceleration(const real x, const real y, const real z){
		this->acceleration.setX(x);this->acceleration.setY(y);this->acceleration.setZ(z);
	}

	void Particle::getAcceleration(Vector3D *acceleration)const{
		*acceleration = this->acceleration;
	}
    Vector3D Particle::getAcceleration()const{
    	return acceleration;
    }

    void Particle::clearAccumulator(){
    	accumulated_force.clear();
    }


