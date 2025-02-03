#include "Drone.h"

Drone::Drone(SDL_Texture* texture, SDL_Rect position, int textureWidth, int textureHeight)
{
	this->texture = texture;
	this->position = position;
	this->posX = position.x;
	this->posY = position.y;
	this->textureWidth = textureWidth;
	this->textureHeight = textureHeight;

	this->frameWidth = 32;
	this->frameHeight = 32;
	this->frameTime = 0.0f;
	this->currentFrame = 0;
	this->numFrames = 16;

	this->spriteRectObject = { 0, 0, frameWidth, frameHeight }; //defaults to the first frame of the sprite

	this->lifePoints = 1;
	this->velocityX = 0.0f;
	this->velocityY = 0.0f;
	this->moveSpeed = 1.0f;
}

Drone::~Drone() {

}

void Drone::Update(float deltaTime)
{
	frameTime += deltaTime;

	// updates animation frames
	if (frameTime >= 0.1f) { // Adjust this value for desired frame speed
		frameTime = 0.0f;

		// Move to the next frame
		currentFrame++;
		if (currentFrame >= numFrames) {
			currentFrame = 0; // Loop back to the first frame
		}

		// Calculate the row and column based on the current frame
		int columns = textureWidth / frameWidth; // Frames per row
		int row = currentFrame / columns;
		int column = currentFrame % columns;

		// Update the spriteRectObject to the correct frame
		spriteRectObject.x = column * frameWidth;
		spriteRectObject.y = row * frameHeight;
	}

	// Update the Drone's position or other behaviors - moves vertically, in a horizontally sinusoidal way and appears in packs
	position.y = static_cast<int>(position.y + moveSpeed);
	position.x = static_cast<int>(100+ 30 * sin(position.y * 0.03));

}

void Drone::Render(Renderer* renderer)
{
	renderer->Render(texture, &spriteRectObject, &position); 
}

SDL_Rect Drone::GetBoundingBox() const {
	return position;
}

void Drone::CreateRigidBody(Physics* physics)
{
	rigidbodyId = physics->CreateDynamicBody(posX, posY, false, 10, 10);
	rigidbodyTransform = physics->GetRigidBodyTransform(rigidbodyId);
	physics->Debug(&rigidbodyTransform, rigidbodyId);
}
