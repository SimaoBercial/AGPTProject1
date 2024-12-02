#include "Enemy.h"
#include <SDL.h>

Enemy::Enemy() { 
}

Enemy::~Enemy() {}

void Enemy::Initialize(SDL_Texture* texture, SDL_Rect startPosition, float speed) {
    this->texture = texture;
    this->position = startPosition;
    this->speed = speed;
}

void Enemy::Update(float deltaTime) {
    position.y += speed * deltaTime;
}

void Enemy::Render() {
    SDL_RenderCopy(renderer, texture, nullptr, &position);
}

SDL_Rect Enemy::GetBoundingBox() const {
    return position;
}
