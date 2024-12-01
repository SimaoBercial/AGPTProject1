#include "Player.h"
#include "Renderer.h"

Player::Player(SDL_Renderer* renderer) {
    texture = Renderer::LoadTexture(renderer, "graphics/Ship1.bmp");
    position = { 100, 100, 50, 50 }; // x, y, width, height
}

void Player::HandleInput() {
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_W]) position.y -= 5;
    if (state[SDL_SCANCODE_S]) position.y += 5;
    if (state[SDL_SCANCODE_A]) position.x -= 5;
    if (state[SDL_SCANCODE_D]) position.x += 5;
}

void Player::Update() {
    // Update player logic
}

void Player::Render(SDL_Renderer* renderer) {
    Renderer::Draw(renderer, texture, nullptr, &position);
}
