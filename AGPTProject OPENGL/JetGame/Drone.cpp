#include "Drone.h"

Drone::Drone(GLuint texture, SDL_Rect position, int textureWidth, int textureHeight)
    : texture(texture),
    frameTime(0.0f),
    currentFrame(0),
    numFrames(16),
    textureWidth(textureWidth),
    textureHeight(textureHeight),
    moveSpeed(1.0f)
{
    this->position = position;
    this->posX = position.x;
    this->posY = position.y;

    this->frameWidth = 32;
    this->frameHeight = 32;
    this->spriteRectObject = { 0, 0, frameWidth, frameHeight };

    this->lifePoints = 1;
    this->velocityX = 0.0f;
    this->velocityY = 0.0f;
}

Drone::~Drone() {}

void Drone::Update(float deltaTime) {
    frameTime += deltaTime;

    // Update animation frames
    if (frameTime >= 0.1f) { // Adjust this value for desired frame speed
        frameTime = 0.0f;

        // Move to the next frame
        currentFrame = (currentFrame + 1) % numFrames;

        // Calculate the row and column based on the current frame
        int columns = textureWidth / frameWidth;
        int row = currentFrame / columns;
        int column = currentFrame % columns;

        // Update spriteRectObject to the correct frame
        spriteRectObject.x = column * frameWidth;
        spriteRectObject.y = row * frameHeight;
    }

    // Moves vertically in a sinusoidal pattern
    posY += moveSpeed;
    posX = 100 + 30 * sin(posY * 0.03);

    // Update position for rendering
    position.x = static_cast<int>(posX);
    position.y = static_cast<int>(posY);
}

void Drone::Render(Renderer* renderer) {
    renderer->Render(texture, spriteRectObject, position);
}

SDL_Rect Drone::GetBoundingBox() const {
    return position;
}

void Drone::CreateRigidBody(Physics* physics) {
    rigidbodyId = physics->CreateDynamicBody(posX, posY, false, 10, 10);
    rigidbodyTransform = physics->GetRigidBodyTransform(rigidbodyId);
    physics->Debug(&rigidbodyTransform, rigidbodyId);
}
