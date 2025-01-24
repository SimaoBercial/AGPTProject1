#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SDL.h"
#include "Renderer.h"
#include "Physics.h"
#include <iostream>

class GameObject {
public:
    virtual ~GameObject() {};

    virtual void Update(float deltaTime) = 0;
    virtual void Render(Renderer* renderer) = 0;
    virtual SDL_Rect GetBoundingBox() const = 0;
	virtual void CreateRigidBody(Physics* physics) = 0;


protected:
    SDL_Texture* texture;
    SDL_Rect position;
    SDL_Rect spriteRectObject;
	int frameWidth;
    int frameHeight;
	float frameTime;
    int currentFrame;
    int numFrames;
    float moveSpeed;
    float movementMagnitude;
    float posX;
    float posY;
    float velocityX;
    float velocityY;
    int textureWidth;
    int textureHeight;

	b2BodyId rigidbodyId;
	b2Transform rigidbodyTransform;
};

#endif
