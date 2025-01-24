#ifndef PHYSICS_H
#define PHYSICS_H

#include "Renderer.h"
#include "box2d.h"


class Physics {
public:
	Physics();
	~Physics();
	b2BodyId CreateStaticBody(float posX, float posY, float width, float height);
	b2BodyId CreateDynamicBody(float posX, float posY, bool isBullet, float width, float height);
	b2Transform GetRigidBodyTransform(b2BodyId bodyId);


private:

	b2WorldDef worldDef = b2DefaultWorldDef();
	b2WorldId worldId = b2CreateWorld(&worldDef);
	float timeStep;
	int subStepCount;
};


#endif 
