#ifndef PHYSICS_H
#define PHYSICS_H

#include "box2d/box2d.h"

class Physics {
public:
	Physics();
	~Physics();

private:
	b2WorldDef worldDef = b2DefaultWorldDef();
	b2WorldId worldId = b2CreateWorld(&worldDef);
	float timeStep;
	int subStepCount;
	void Box2DDebug();
};


#endif 
