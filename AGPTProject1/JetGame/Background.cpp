#include "Background.h"
#include <iostream>

Background::Background() {}

Background::~Background() {
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(parallaxTexture);
	
}

void Background::Initialize(SDL_Texture& backgroundTexture, SDL_Texture& parallaxTexture,
	float scrollSpeed, int width, int height)
{
	this->screenWidth = width;
	this->screenHeight = height;
	this->scrollSpeed = scrollSpeed;
	this->backgroundTexture = &backgroundTexture;
	this->parallaxTexture = &parallaxTexture;
	this->background = { 0, 0, width, height }; 
	this->spriteRect = { 0, 1536, 192, 96 };
	this->parallax = { 0, -screenHeight,spriteRect.w, spriteRect.h };
}

void Background::Update(float deltaTime)
{
	parallax.y += scrollSpeed ;
	if (parallax.y >= screenHeight) 
	{
		parallax.y = -screenHeight;
	}
}

void Background::Render(Renderer* renderer)
{
	renderer->Render(backgroundTexture, nullptr, &background);// called first, is in the first layer of background
	renderer->Render(parallaxTexture, &spriteRect, &parallax);// called after, is in the second layer of the background
}