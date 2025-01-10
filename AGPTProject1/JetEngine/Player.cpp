// #include "Player.h"
// #include "Renderer.h"
// #include "Missile.h"
// #include <iostream>
// 
// Player::Player()
//     : texture(nullptr),
//     moveSpeed(200.0f),
//     currentFrame(0),
//     frameTime(0.0f),
//     numFrames(7),
//     frameWidth(64),
//     frameHeight(64),
//     movingLeft(false),
//     movingRight(false),
//     missileTexture(nullptr),
//     missileCooldown(0.2f),
//     missileTimer(0.0f),
//     movementMagnitude(0.0f)
// {}
// 
// Player::~Player() {}
// 
// void Player::Initialize(SDL_Texture* playerTexture, SDL_Texture* missileTexture, const SDL_Rect& startPosition) {
//     texture = playerTexture;
//     this->missileTexture = missileTexture;
//     position = startPosition;
// 	spriteRectPlayer = { 0, 0, frameWidth, frameHeight };
//     posX = startPosition.x;
//     posY = startPosition.y;
// }
// 
// void Player::HandleInput(const Uint8* keyState, float deltaTime, InputManager* inputManager) {
//     
//     
//     HandleShooting(inputManager, deltaTime);
// }
// 
// void Player::HandleShooting(InputManager* inputManager, float deltaTime) {
//     missileTimer -= deltaTime;
// 
//     bool shootKey = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_SPACE];
//     bool shootButton = inputManager->IsButtonPressed(SDL_CONTROLLER_BUTTON_A);
// 
//     if ((shootKey || shootButton) && missileTimer <= 0.0f) {
//         SDL_Rect missileStartPos = { position.x + position.w / 2 - 8, position.y - 16, 16, 32 };
//         Missile missile;
//         missile.Initialize(missileTexture, missileStartPos, 500.0f);
//         missiles.push_back(missile);
//         missileTimer = missileCooldown;
//     }
// }
// 
// void Player::Update(float deltaTime) {
//     UpdateAnimation(deltaTime);
// 
//     for (auto it = missiles.begin(); it != missiles.end();) {
//         it->Update(deltaTime, 32, 48, 16, 16);
//         if (it->IsOffScreen()) {
//             it = missiles.erase(it); 
//         }
//         else {
//             ++it;
//         }
//     }
// }
// 
// void Player::UpdateAnimation(float deltaTime) { //convert to Animation Class
//     if (!movingLeft && !movingRight) {
//         currentFrame = 3;
//         frameTime = 0.0f;
//         spriteRectPlayer.x = currentFrame * frameWidth;
//         return;
//     }
// 
//     frameTime += deltaTime;
//     if (frameTime >= 0.1f) {
//         frameTime = 0.0f;
// 
//         if (movingLeft) {
//             currentFrame--;
//             if (currentFrame < 0) {
//                 currentFrame = 0;
//             }
//         }
//         else if (movingRight) {
//             currentFrame++;
//             if (currentFrame > 6) {
//                 currentFrame = 6;
//             }
//         }
//     }
//     spriteRectPlayer.x = currentFrame * frameWidth;
// }
// 
// void Player::Render(Renderer* renderer) {
//     renderer->Render(texture, &spriteRectPlayer, &position);
// 
//     for (auto& missile : missiles) {
//         missile.Render();
//     }
// }
