#include "Background.h"

Background::Background() : backgroundTexture(0), parallaxTexture(0), scrollSpeed(0.0f), screenWidth(0), screenHeight(0) {}

Background::~Background() {
}

void Background::Initialize(GLuint backgroundTexture, GLuint parallaxTexture, float scrollSpeed, int width, int height) {
    this->screenWidth = width;
    this->screenHeight = height;
    this->scrollSpeed = scrollSpeed;
    this->backgroundTexture = backgroundTexture;
    this->parallaxTexture = parallaxTexture;

    this->background = { 0, 0, width, height };
    this->spriteRect = { 0, 1536, 192, 96 };
    this->parallax = { 0, -screenHeight, spriteRect.w, spriteRect.h };
}

void Background::Update(float deltaTime) {
    parallax.y += scrollSpeed;
    if (parallax.y >= screenHeight) {
        parallax.y = -screenHeight;
    }
}

void Background::Render(Renderer* renderer) {
    renderer->Render(backgroundTexture, { 0, 0, screenWidth, screenHeight }, background);
    renderer->Render(parallaxTexture, spriteRect, parallax);
}
