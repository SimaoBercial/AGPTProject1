#include "Rusher.h"

Rusher::Rusher(GLuint texture, SDL_Rect position, int textureWidth, int textureHeight)
    : texture(texture)
{
    this->position = position;
    this->posX = position.x;
    this->posY = position.y;
    this->textureWidth = textureWidth;
    this->textureHeight = textureHeight;

    this->frameWidth = 64;
    this->frameHeight = 32;
    this->frameTime = 0.0f;
    this->currentFrame = 0;
    this->numFrames = 24;

    this->spriteRectObject = { 0, 0, frameWidth, frameHeight }; // Defaults to the first frame of the sprite

    this->lifePoints = 1;
    this->velocityX = 0.0f;
    this->velocityY = 0.0f;
    this->moveSpeed = 1.0f;
}

Rusher::~Rusher() {}

void Rusher::Update(float deltaTime)
{
    frameTime += deltaTime;

    // Updates animation frames
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

    // Update the Rusher's position or other behaviors -- moves vertically
    position.y = static_cast<int>(position.y + moveSpeed);
}

void Rusher::Render(Renderer* renderer)
{
    renderer->Render(texture, spriteRectObject, position);
}

SDL_Rect Rusher::GetBoundingBox() const {
    return position;
}

void Rusher::CreateRigidBody(Physics* physics)
{
    rigidbodyId = physics->CreateDynamicBody(posX, posY, false, 10, 10);
    rigidbodyTransform = physics->GetRigidBodyTransform(rigidbodyId);
    physics->Debug(&rigidbodyTransform, rigidbodyId);
}
