#include "Spaceship.h"

Spaceship::Spaceship(GLuint texture, SDL_Rect position)
    : texture(texture),
    missileTexture(0),
    companionTexture(0),
    missileTimer(0.0f),
    missileCooldown(0.2f),
    lifePoints(100),
    maxWeaponPowerUp(2),
    weaponPowerUp(0),
    companionsNumber(0),
    maxCompanionsNumber(2),
    rigidbodyId(b2_nullShapeId),
    rigidbodyTransform(b2Transform_identity),
    missiles{},
    companions{},
    physics(nullptr) {

    this->position = position;
    this->frameWidth = 64;
    this->frameHeight = 64;
    this->spriteRectPlayer = { 0, 0, frameWidth, frameHeight };

    this->posX = position.x;
    this->posY = position.y;

    this->frameTime = 0.0f;
    this->numFrames = 7;
    this->currentFrame = 3;

    this->moveSpeed = 200.0f;
    this->velocityX = 0.0f;
    this->velocityY = 0.0f;

    this->movingLeft = false;
    this->movingRight = false;
    this->movingUp = false;
    this->movingDown = false;
}

void Spaceship::GetScreenSize(float screenWidth, float screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    for (auto& companion : companions) {
        companion.screenWidth = screenWidth;
        companion.screenHeight = screenHeight;
    }
}

void Spaceship::StoreMissileTexture(GLuint missileTexture) {
    this->missileTexture = missileTexture;
}

void Spaceship::StoreCompanionTexture(GLuint companionTexture) {
    this->companionTexture = companionTexture;
}

void Spaceship::HandleInput(const Uint8* keyState, float deltaTime, InputManager* inputManager) {
    float velocityX = 0.0f;
    float velocityY = 0.0f;

    for (auto& companion : companions) {
        companion.velocityX = 0.0f;
        companion.velocityY = 0.0f;
    }

    if (keyState[SDL_SCANCODE_D]) {
        velocityX += 1.0f;
        movingLeft = false;
        movingRight = true;
    }
    if (keyState[SDL_SCANCODE_A]) {
        velocityX -= 1.0f;
        movingLeft = true;
        movingRight = false;
    }
    if (keyState[SDL_SCANCODE_W]) {
        velocityY -= 1.0f;
        movingUp = true;
        movingDown = false;
    }
    if (keyState[SDL_SCANCODE_S]) {
        velocityY += 1.0f;
        movingUp = false;
        movingDown = true;
    }

    if (inputManager->IsGamepadConnected()) {
        float axisX = inputManager->GetAxis(SDL_CONTROLLER_AXIS_LEFTX);
        float axisY = inputManager->GetAxis(SDL_CONTROLLER_AXIS_LEFTY);

        velocityX += axisX;
        velocityY += axisY;
    }

    movementMagnitude = std::sqrt(velocityX * velocityX + velocityY * velocityY);
    if (movementMagnitude > 0.0f) {
        velocityX /= movementMagnitude;
        velocityY /= movementMagnitude;
    }

    posX += velocityX * moveSpeed * deltaTime;
    posY += velocityY * moveSpeed * deltaTime;

    position.x = static_cast<int>(posX);
    position.y = static_cast<int>(posY);

    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;
    if (position.x + position.w > screenWidth) position.x = screenWidth - position.w;
    if (position.y + position.h > screenHeight) position.y = screenHeight - position.h;

    HandleShooting(inputManager, deltaTime);
}

void Spaceship::Update(float deltaTime) {
    UpdateAnimation(deltaTime);

    for (auto& companion : companions) {
        companion.Update(deltaTime);
    }

    for (auto it = missiles.begin(); it != missiles.end();) {
        it->Update(deltaTime);
        if (it->IsOffScreen()) {
            it = missiles.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Spaceship::UpdateAnimation(float deltaTime) {
    if (!movingLeft && !movingRight) {
        currentFrame = 3;
        spriteRectPlayer.x = currentFrame * frameWidth;
        return;
    }

    frameTime += deltaTime;
    if (frameTime >= 0.1f) {
        frameTime = 0.0f;

        if (movingLeft) {
            currentFrame = std::max(0, currentFrame - 1);
        }
        else if (movingRight) {
            currentFrame = std::min(6, currentFrame + 1);
        }
    }
    spriteRectPlayer.x = currentFrame * frameWidth;
}

void Spaceship::HandleShooting(InputManager* inputManager, float deltaTime) {
    missileTimer -= deltaTime;

    bool shootKey = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_SPACE];
    bool shootButton = inputManager->IsButtonPressed(SDL_CONTROLLER_BUTTON_A);

    if ((shootKey || shootButton) && missileTimer <= 0.0f) {
        Missile missile(missileTexture, { position.x + position.w / 2 - 8, position.y - 16, 16, 16 }, weaponPowerUp);
        missiles.push_back(missile);
        missile.CreateRigidBody(physics);
        missileTimer = missileCooldown;
    }
}

void Spaceship::Render(Renderer* renderer) {
    renderer->Render(texture, spriteRectPlayer, position);

    for (auto& missile : missiles) {
        missile.Render(renderer);
    }
    for (auto& companion : companions) {
        companion.Render(renderer);
    }

    physics->Debug(&rigidbodyTransform, rigidbodyId);
}

void Spaceship::CreateRigidBody(Physics* physics) {
    rigidbodyId = physics->CreateDynamicBody(posX, posY, true, 30, 20);
    rigidbodyTransform = physics->GetRigidBodyTransform(rigidbodyId);
    this->physics = physics;
}

void Spaceship::WeaponPowerUp() {
    if (weaponPowerUp < maxWeaponPowerUp) {
        weaponPowerUp++;
    }
}

void Spaceship::ShieldPowerUp() {}

Spaceship::~Spaceship() {}
