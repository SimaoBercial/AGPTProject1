#include "Enemy.h"
#include <SDL.h>

Enemy::Enemy() { 
}

Enemy::~Enemy() {}

void Enemy::Initialize(SDL_Texture* texture, SDL_Rect startPosition, float scrollSpeed) {
    this->texture = texture;
    this->position = startPosition;
    this->speed = scrollSpeed;
    this->renderer = SDL_GetRenderer(SDL_GetWindowFromID(1));
}

void Enemy::Update(float deltaTime, int textureWidth, int textureHeight, int frameWidth, int frameHeigth) {
    
}

void Enemy::Render() {
	SDL_RenderCopy(renderer, texture, nullptr, &position);
}

SDL_Rect Enemy::GetBoundingBox() const {
    return position;
}
