#include "Physics.h"


Physics::Physics() {
	worldDef.gravity = {0.0f, 0.0f};
	timeStep = 1.0f / 60.0f;
	subStepCount = 4;
	
}

Physics::~Physics(){
	b2DestroyWorld(worldId);
}

void Physics::CreateStaticBody(float posX, float posY, float width, float height)
{
	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_staticBody;
	bodyDef.position = { posX, posY };

	b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

	b2Polygon dynamicBox = b2MakeBox(width / 2, height / 2);

	b2ShapeDef shapeDef = b2DefaultShapeDef();
	b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
}

void Physics::CreateDynamicBody(float posX, float posY, bool isBullet, float width, float height)
{
	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_staticBody;
	bodyDef.position = { posX, posY };
	bodyDef.isBullet = isBullet;

	b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

	b2Polygon dynamicBox = b2MakeBox(width / 2, height / 2);

	b2ShapeDef shapeDef = b2DefaultShapeDef();
	b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
}
