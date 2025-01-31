#include "Companion.h"

Companion::Companion(GLuint texture, SDL_Rect position, int textureWidth, int textureHeight)
    : missileTimer(0.0f),
    missileCooldown(0.2f),
    maxWeaponPowerUp(2),
    weaponPowerUp(0),
    lifePoints(10),
    screenWidth(0),
    screenHeight(0),
    rigidbodyId(b2_nullShapeId),
    rigidbodyTransform(b2Transform_identity),
    missileTexture(0), 
    movingRight(false),
    movingLeft(false),
    movingDown(false),
    movingUp(false),
    missiles{}
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
    this->numFrames = 20;

    this->spriteRectObject = { 0, 0, frameWidth, frameHeight };

    this->moveSpeed = 200.0f;
    this->velocityX = 0.0f;
    this->velocityY = 0.0f;
}

Companion::~Companion() {}

void Companion::Movement(float deltaTime) {
    movementMagnitude = std::sqrt(velocityX * velocityX + velocityY * velocityY); // Normalize diagonal movement
    if (movementMagnitude > 0.0f) {
        velocityX /= movementMagnitude;
        velocityY /= movementMagnitude;
    }
    posX += velocityX * moveSpeed * deltaTime;
    posY += velocityY * moveSpeed * deltaTime;

    // Update position for rendering (rounded to integers for SDL_Rect)
    position.x = static_cast<int>(posX);
    position.y = static_cast<int>(posY);

    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;

    if (velocityX == 0.0f && velocityY == 0.0f) {
        movingLeft = false;
        movingRight = false;
        movingUp = false;
        movingDown = false;
    }
}

void Companion::Update(float deltaTime)
{
    UpdateAnimation(deltaTime);

    for (auto it = missiles.begin(); it != missiles.end();) {
        it->Update(deltaTime);
        if (it->IsOffScreen()) {
            it = missiles.erase(it);
        }
        else {
            ++it;
        }
    }
    // Additional collision checks can be done here if needed.
}

void Companion::Render(Renderer* renderer)
{
    renderer->Render(texture, spriteRectObject, position); // Render companion
    for (auto& missile : missiles) {
        missile.Render(renderer); // Render missiles
    }
    physics->Debug(&rigidbodyTransform, rigidbodyId); // Physics debugging, if necessary
}

SDL_Rect Companion::GetBoundingBox() const
{
    return position;
}

void Companion::CreateRigidBody(Physics* physics)
{
    rigidbodyId = physics->CreateDynamicBody(posX, posY, true, 1, 1);
    rigidbodyTransform = physics->GetRigidBodyTransform(rigidbodyId);
    this->physics = physics;
}

void Companion::ShootMissile(GLuint missileTexture)
{
    this->missileTexture = missileTexture;
    Missile missile(missileTexture, { (position.x + position.w / 2) - 8, (position.y - 16), 16, 16 }, weaponPowerUp);
    missile.CreateRigidBody(physics);
    missiles.push_back(missile);
    missileTimer = missileCooldown;
}

void Companion::UpdateAnimation(float deltaTime)
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
}

void Companion::WeaponPowerUp()
{
    if (weaponPowerUp != maxWeaponPowerUp) { weaponPowerUp++; }
    else(weaponPowerUp == maxWeaponPowerUp);
}

void Companion::ShieldPowerUp()
{
}
