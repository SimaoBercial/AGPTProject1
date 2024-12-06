#include "Enemy.h"
#include <SDL.h>

Enemy::Enemy() {
}

Enemy::~Enemy() {}

void Enemy::Initialize(SDL_Texture* texture, SDL_Rect startPosition, float scrollSpeed, int frameWidth, int frameHeigth) {
	this->texture = texture;
	this->position = startPosition;
	this->speed = scrollSpeed;
	this->renderer = SDL_GetRenderer(SDL_GetWindowFromID(1));
	frameRect.x = frameRect.y = 0;
	frameTime = 0;
}
void Enemy::SetEnemy(bool isLoner, bool isRusher) {
	this->isLoner = isLoner;
	this->isRusher = isRusher;
}

void Enemy::Update(float deltaTime, int textureWidth, int textureHeight, int frameWidth, int frameHeight) {
	frameRect.w = frameWidth;
	frameRect.h = frameHeight;
	frameTime++;
	if (frameTime >= 15)
	{
		frameTime = 0;
		frameRect.x += frameWidth;
		if (frameRect.x >= textureWidth) {
			frameRect.x = 0;
			frameRect.y += frameHeight;
			if (frameRect.y >= textureHeight) {
				frameRect.y = 0;
			}
		}
	}
	if (isRusher) {
		position.y = static_cast<int>(position.y + speed);
	}
	else if (isLoner) {
		position.x = static_cast<int>(position.x + speed);
	}

}


void Enemy::Render() {
	SDL_RenderCopy(renderer, texture, &frameRect, &position);
}

SDL_Rect Enemy::GetBoundingBox() const {
	return position;
}
