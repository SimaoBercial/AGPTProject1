#include "Window.h"
#include "SDL.h"

Window::Window() {
	window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
}

Window::~Window() {
	SDL_DestroyWindow(window);
}

SDL_Renderer* SetRenderTarget(SDL_Window* window, int index, Uint32 flags)
{
	SDL_Renderer* renderTarget = nullptr;
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	return renderTarget;
}


