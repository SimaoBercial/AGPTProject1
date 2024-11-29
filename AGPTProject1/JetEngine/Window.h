#pragma once
#include "C:\Users\Sauchixa\Desktop\AGPTProject1\AGPTProject1\Vendor\SDL2\include\SDL.h"
#include <iostream>

class Window
{
public:
	Window();
	~Window();

	SDL_Renderer* SetRenderTarget();
	SDL_Texture* LoadTexture(std::string filePath);
	
	
private:
	class SDL_Window* window = nullptr;
	class SDL_Renderer* renderTarget = nullptr;
	class SDL_Texture* texture = nullptr;
	class SDL_Surface* surface = nullptr;
};

