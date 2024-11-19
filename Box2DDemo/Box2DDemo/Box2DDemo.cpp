#include <iostream>
#include <box2d/box2d.h>

int main()
{
    //World Definition
    b2WorldDef worldDef = b2DefaultWorldDef();

    //Gravity Vector
    b2Vec2 gravity{0.0f, -10.0f};

    //Construct world object
    b2WorldId worldId = b2CreateWorld(&worldDef);

    //Define the ground body
    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = {0, -10};

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);

    b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);

    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = { 0.0f, 4.0f };

    b2BodyId  bodyId = b2CreateBody(worldId, &bodyDef);
    
    b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);

    b2ShapeDef shapeDef = b2DefaultShapeDef();

    shapeDef.density = 1.0f;

    shapeDef.friction = 0.3f;

    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

    float timeStep = 1.0f / 60.0f;
    int substepCount = 4;

    b2Vec2 position = b2Body_GetPosition(bodyId);
    b2Rot rotation = b2Body_GetRotation(bodyId);

    for (int i = 0; i < 90; ++i) {
        b2World_Step(worldId, timeStep, substepCount);

        position = b2Body_GetPosition(bodyId);
        rotation = b2Body_GetRotation(bodyId);

        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, rotation);
    }

    b2DestroyWorld(worldId);

}