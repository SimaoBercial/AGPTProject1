#include "Player.h"
#include "Renderer.h"
#include "Missile.h"

Player::Player()
    : texture(nullptr),
    moveSpeed(200.0f),
    currentFrame(0),
    frameTime(0.0f),
    numFrames(7),
    frameWidth(64),
    frameHeight(64),
    movingLeft(false),
    movingRight(false), 
    missileTexture(nullptr),
    missileCooldown(0.2f),
    missileTimer(0.0f) {
}

Player::~Player() {}

void Player::Initialize(SDL_Texture* playerTexture, SDL_Texture* missileTexture, const SDL_Rect& startPosition) {
    texture = playerTexture;
    this->missileTexture = missileTexture;
    position = startPosition;
    spriteRect = { 0, 0, frameWidth, frameHeight };
}

void Player::HandleInput(const Uint8* keyState, float deltaTime, InputManager* inputManager) {
    float moveX = 0.0f;
    float moveY = 0.0f;

    if (keyState[SDL_SCANCODE_D]) {
        moveX += 1.0f;
        movingLeft = false;
        movingRight = true;
    }
    if (keyState[SDL_SCANCODE_A]) {
        moveX -= 1.0f;
        movingLeft = true;
        movingRight = false;
    }
    if (keyState[SDL_SCANCODE_W]) {
        moveY -= 1.0f;
    }
    if (keyState[SDL_SCANCODE_S]) {
        moveY += 1.0f;
    }

    if (inputManager->IsGamepadConnected()) {
        float axisX = inputManager->GetAxis(SDL_CONTROLLER_AXIS_LEFTX);
        float axisY = inputManager->GetAxis(SDL_CONTROLLER_AXIS_LEFTY);

        moveX += axisX;
        moveY += axisY;

        if (axisX > 0.1f) {
            movingLeft = false;
            movingRight = true;
        }
        else if (axisX < -0.1f) {
            movingLeft = true;
            movingRight = false;
        }
    }

    position.x += moveX * moveSpeed * deltaTime;
    position.y += moveY * moveSpeed * deltaTime;

    const int screenWidth = 640; 
    const int screenHeight = 480; 
    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;
    if (position.x + position.w > screenWidth) position.x = screenWidth - position.w;
    if (position.y + position.h > screenHeight) position.y = screenHeight - position.h;

    if (moveX == 0.0f && moveY == 0.0f) {
        movingLeft = false;
        movingRight = false;
    }

    HandleShooting(inputManager, deltaTime);
}

void Player::HandleShooting(InputManager* inputManager, float deltaTime) {
    missileTimer -= deltaTime;

    bool shootKey = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_SPACE];
    bool shootButton = inputManager->IsButtonPressed(SDL_CONTROLLER_BUTTON_A);

    if ((shootKey || shootButton) && missileTimer <= 0.0f) {
        SDL_Rect missileStartPos = { position.x + position.w / 2 - 8, position.y - 16, 16, 32 };
        Missile missile;
        missile.Initialize(missileTexture, missileStartPos, 500.0f);
        missiles.push_back(missile);
        missileTimer = missileCooldown;
    }
}

void Player::Update(float deltaTime) {
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
}

void Player::UpdateAnimation(float deltaTime) {
    if (!movingLeft && !movingRight) {
        currentFrame = 3;
        frameTime = 0.0f;
        spriteRect.x = currentFrame * frameWidth;
        return;
    }

    frameTime += deltaTime;
    if (frameTime >= 0.1f) {
        frameTime = 0.0f;

        if (movingLeft) {
            currentFrame--;
            if (currentFrame < 0) {
                currentFrame = 0;
            }
        }
        else if (movingRight) {
            currentFrame++;
            if (currentFrame > 6) {
                currentFrame = 6;
            }
        }
    }
    spriteRect.x = currentFrame * frameWidth;
}

void Player::Render(Renderer* renderer) {
    renderer->Render(texture, &spriteRect, &position);

    for (auto& missile : missiles) {
        missile.Render();
    }


}
