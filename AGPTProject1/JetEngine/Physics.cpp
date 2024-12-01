/*
#include "Physics.h"

b2World* Physics::CreateWorld() {
    return new b2World(b2Vec2(0.0f, -9.8f)); // Gravity in -y
}

void Physics::Update(b2World* world, float timeStep) {
    const int32 velocityIterations = 6;
    const int32 positionIterations = 2;
    world->Step(timeStep, velocityIterations, positionIterations);
}
*/