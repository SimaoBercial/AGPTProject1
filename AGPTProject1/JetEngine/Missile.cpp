#include "Missile.h"

Missile::Missile(SDL_Texture* texture, SDL_Rect position, int missilePowerUpSprite): damage(1)
{
    this->texture = texture;
    this->position = position;
    this->posX = position.x;
    this->posY = position.y;

    this->frameWidth = 16;
    this->frameHeight = 16;
    this->frameTime = 0.0f;
    this->currentFrame = 0;
    this->numFrames = 6;
    this->missilePowerUpSprite = missilePowerUpSprite; //receives from SpaceShip and Companions the multiplier (0, 1 or 2) to change the spriteRectObject position.y
                                                       //of the texture (to 0, 16 or 32, respectively), changing the missiles with the powerUps
    this->spriteRectObject = { 0, 16*missilePowerUpSprite, frameWidth, frameHeight };

    this->velocityX = 0.0f;
    this->velocityY = 0.0f;
    this->moveSpeed = 2.0f; //speed of the missile
}

Missile::~Missile() {

}

void Missile::Update(float deltaTime) {
	position.y = static_cast<int>(position.y - moveSpeed);
}

void Missile::Render(Renderer* renderer) {
    if (renderer && texture) {
        renderer->Render(texture, &spriteRectObject, &position);
    }

}

SDL_Rect Missile::GetBoundingBox() const {
    return position;
}

void Missile::CreateRigidBody(Physics* physics)
{
	rigidbodyId = physics->CreateDynamicBody(posX, posY, true, 10, 10);
	rigidbodyTransform = physics->GetRigidBodyTransform(rigidbodyId);
	physics->Debug(&rigidbodyTransform, rigidbodyId);
}

bool Missile::IsOffScreen() const {
    return position.y + position.h < 0;
}
