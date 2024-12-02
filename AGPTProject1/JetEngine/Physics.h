#ifndef PHYSICS_H
#define PHYSICS_H

#include <box2d/box2d.h>

class Physics {
public:
    static b2World* CreateWorld();
    static void Update(b2World* world, float timeStep);
};

#endif 
