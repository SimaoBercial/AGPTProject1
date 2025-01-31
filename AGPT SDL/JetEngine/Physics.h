#ifndef PHYSICS_H
#define PHYSICS_H

#include "Renderer.h"
#include "box2d.h"
#include <iostream>


class Physics {
public:
	Physics();
	~Physics();
	b2WorldId GetWorld();
	b2ShapeId CreateStaticBody(float posX, float posY, bool isSensor, float width, float height);
	b2ShapeId CreateDynamicBody(float posX, float posY, bool isSensor, float width, float height);
	b2Transform GetRigidBodyTransform(b2ShapeId shapeId);
	void UpdatePhysics();
	void DetectCollision(b2SensorBeginTouchEvent collision);
	void Debug(b2Transform* bodyTransform, b2ShapeId shapeId);
	void SetRenderer(Renderer* renderer);

private:
	Renderer* renderer;
	b2WorldDef worldDef = b2DefaultWorldDef();
	b2WorldId worldId = b2CreateWorld(&worldDef);
	float timeStep;
	int subStepCount;
};

#endif 
