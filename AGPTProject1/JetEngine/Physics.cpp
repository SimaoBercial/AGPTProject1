#include "Physics.h"
#include "box2d/box2d.h"


Physics::Physics() {
	worldDef.gravity = {0.0f, 0.0f};
	timeStep = 1.0f / 60.0f;
	subStepCount = 4;
}

Physics::~Physics(){
	b2DestroyWorld(worldId);
}


