#include "Physics.h"


Physics::Physics() {
	worldDef.gravity = {0.0f, 0.0f};
	timeStep = 1.0f / 60.0f;
	subStepCount = 4;
	
}

Physics::~Physics(){
	b2DestroyWorld(worldId);
}

Physics::CreateStaticBody(float posX, float posY)
{

}
