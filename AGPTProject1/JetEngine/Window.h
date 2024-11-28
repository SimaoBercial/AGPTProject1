#pragma once

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

