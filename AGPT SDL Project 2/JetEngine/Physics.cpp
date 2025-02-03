#include "Physics.h"

Physics::Physics() {
	worldDef.gravity = {0.0f, 0.0f};
	timeStep = 1.0f / 60.0f;
	subStepCount = 4;
	b2SensorEvents sensorEvents = b2World_GetSensorEvents(worldId);
}

Physics::~Physics(){
	b2DestroyWorld(worldId);
}

b2WorldId Physics::GetWorld() {
	return worldId;
}

b2ShapeId Physics::CreateStaticBody(float posX, float posY, bool isSensor, float width, float height)
{
	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_staticBody;
	bodyDef.position = { posX, posY };

	b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

	b2Polygon dynamicBox = b2MakeBox(width / 2, height / 2);

	b2ShapeDef shapeDef = b2DefaultShapeDef();
	shapeDef.isSensor = isSensor;
	b2ShapeId shapeId = b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

	return shapeId;
}

b2ShapeId Physics::CreateDynamicBody(float posX, float posY, bool isSensor, float width, float height)
{
	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = { posX, posY };

	b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

	b2Polygon dynamicBox = b2MakeBox(width / 2, height / 2);

	b2ShapeDef shapeDef = b2DefaultShapeDef();
	shapeDef.isSensor = isSensor;
	b2ShapeId shapeId = b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

	return shapeId;
}

b2Transform Physics::GetRigidBodyTransform(b2ShapeId shapeId)
{
	b2BodyId bodyId = b2Shape_GetBody(shapeId);
	return b2Body_GetTransform(bodyId);
}

void Physics::UpdatePhysics()
{
	b2World_Step(worldId, timeStep, subStepCount);
	
}

void Physics::DetectCollision(b2SensorBeginTouchEvent collision)
{
	b2ShapeId* sensorShape = &collision.sensorShapeId;
	b2ShapeId* visitorShape = &collision.visitorShapeId;

	std::cout << sensorShape << " detected " << visitorShape << std::endl;
}

void Physics::Debug(b2Transform* bodyTransform, b2ShapeId shapeId)
{
	b2Vec2 position = bodyTransform->p;
	b2Rot angle = bodyTransform->q;

	b2Polygon bodyPolygon = b2Shape_GetPolygon(shapeId);
	b2Vec2 vertex1 = bodyPolygon.vertices[0];
	b2Vec2 vertex2 = bodyPolygon.vertices[1];
	b2Vec2 vertex3 = bodyPolygon.vertices[2];
	b2Vec2 vertex4 = bodyPolygon.vertices[3];

	float width = vertex2.x - vertex1.x;
	float height = vertex3.y - vertex1.y;

	// Convert Box2D's position from meters to pixels (assuming 1 meter = 30 pixels)
	int posX = static_cast<int>(position.x );
	int posY = static_cast<int>(position.y );

	SDL_Rect rect = {
				posX - static_cast<int>(width),  // Adjust X for the center of the body
				posY - static_cast<int>(height), // Adjust Y for the center of the body
				static_cast<int>(width),         // Width scaled to pixels
				static_cast<int>(height)         // Height scaled to pixels
	};

	renderer->Debug(rect);
}

void Physics::SetRenderer(Renderer* renderer) // FOR DEBUGGING PURPOSES ONLY
{
	this->renderer = renderer;
}



