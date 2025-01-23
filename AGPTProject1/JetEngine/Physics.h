#ifndef PHYSICS_H
#define PHYSICS_H

#include "Renderer.h"
#include "box2d/box2d.h"


class Physics {
public:
	Physics();
	~Physics();
	void CreateStaticBody(float posX, float posY, float width, float height); 
	void CreateDynamicBody(float posX, float posY, bool isBullet, float width, float height);

private:
	b2WorldDef worldDef = b2DefaultWorldDef();
	b2WorldId worldId = b2CreateWorld(&worldDef);
	float timeStep;
	int subStepCount;
};


#endif 
