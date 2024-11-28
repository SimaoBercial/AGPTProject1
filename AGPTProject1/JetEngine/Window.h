#pragma once
#include "D:\Desktop\AGPTProject1\AGPTProject1\Vendor\SDL2\include\SDL.h"

class Window
{
public:
	Window();
	~Window();

	SDL_Renderer* SetRenderTarget();
	
private:
	class SDL_Window* window = nullptr;
	class SDL_Renderer* renderTarget = nullptr;
};

