#include "Missile.h"

Missile::Missile()
    : texture(nullptr),
    speed(500.0f),
    frameWidth(16),
    frameHeight(16)
{}

Missile::~Missile() {}

void Missile::Initialize(SDL_Texture* texture, SDL_Rect startPosition, float speed) {
    this->texture = texture;
    this->position = startPosition;
    this->speed = speed;
    spriteRectMissile = { 0, 0, frameWidth, frameHeight };
    this->renderer = SDL_GetRenderer(SDL_GetWindowFromID(1));
}


void Missile::Update(float deltaTime) {
    position.y = static_cast<int>(position.y - speed * deltaTime);
}

void Missile::Render() {
    if (renderer && texture) {
        SDL_RenderCopy(renderer, texture, &spriteRectMissile, &position);
    }
}

SDL_Rect Missile::GetBoundingBox() const {
    return position;
}

bool Missile::IsOffScreen() const {
    return position.y + position.h < 0;
}
