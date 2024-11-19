#pragma once

class Window
{
public:
	Window();
	~Window();
	SDL_Renderer* SetRenderTarget(SDL_Window* window, int index, Uint32 flags);

private:
	class SDL_Window* window;

};

