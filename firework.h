#ifndef FIREWORK_H
#define FIREWORK_H

#include "particle.h"

class Firework: public Particle
{
public:
    unsigned type;
    real age;
};

struct FireworkRule
{
    unsigned type;
    real min_age;
    real max_age;
    Vector3D min_velocity;
    Vector3D max_velocity;
    real damping;

    struct Payload //what carry the fw, this is the new firework to create when the current fw die
    {
        unsigned type; //type of new particles to create, aka sub particles part of the payload
        unsigned count; //number of particles in this payload
    };

    unsigned payload_count; //number of payload for this type of fw
    Payload* payloads; //Set of payloads
};

#endif // FIREWORK_H
