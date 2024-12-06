#include "Player.h"
#include "Renderer.h"
#include "Missile.h"
#include <iostream>

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
    missileTimer(0.0f),
    movementMagnitude(0.0f)
{}

Player::~Player() {}

void Player::Initialize(SDL_Texture* playerTexture, SDL_Texture* missileTexture, const SDL_Rect& startPosition) {
    texture = playerTexture;
    this->missileTexture = missileTexture;
    position = startPosition;
	spriteRectPlayer = { 0, 0, frameWidth, frameHeight };
    posX = startPosition.x;
    posY = startPosition.y;
}

void Player::HandleInput(const Uint8* keyState, float deltaTime, InputManager* inputManager) {
    float moveX = 0.0f;
    float moveY = 0.0f;

    if (keyState[SDL_SCANCODE_D]) {
        moveX += 1.0f ;
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

    movementMagnitude  = std::sqrt(moveX * moveX + moveY * moveY); //normalize diagonal movement
	if (movementMagnitude > 0.0f) {
		moveX /= movementMagnitude;
		moveY /= movementMagnitude;
	}
    //calculates the movement speed with precision, using float point precision
    posX += moveX * moveSpeed * deltaTime; 
    posY += moveY * moveSpeed * deltaTime;

    //takes the movement precision value, then rounds up, 
    //converting and rounding the float to a integer, 
    //for the rendering of SDL_Rect
    position.x = static_cast<int>(posX);
    position.y = static_cast<int>(posY);    

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
        it->Update(deltaTime, 32, 48, 16, 16);
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
        spriteRectPlayer.x = currentFrame * frameWidth;
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
    spriteRectPlayer.x = currentFrame * frameWidth;
}

void Player::Render(Renderer* renderer) {
    renderer->Render(texture, &spriteRectPlayer, &position);

    for (auto& missile : missiles) {
        missile.Render();
    }


}
