#ifndef PHYSICS_H
#define PHYSICS_H

#include "Renderer.h"
#include "box2d/box2d.h"


class Physics {
public:
	Physics();
	~Physics();
	void CreateStaticBody(float posX, float posY); // maybe instead of void have a b2BodyDef or something, idk
	void CreateDynamicBody(float posX, float posY, bool isBullet);
	void CreateShape(float density, bool hasSensorEvents);

private:
	b2WorldDef worldDef = b2DefaultWorldDef();
	b2WorldId worldId = b2CreateWorld(&worldDef);
	float timeStep;
	int subStepCount;
};


#endif 
