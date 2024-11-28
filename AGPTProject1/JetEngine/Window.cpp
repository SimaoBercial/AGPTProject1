#include "Window.h"
#include "SDL.h"
#include <iostream>

Window::Window() {
	window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
}

Window::~Window() {
	if (renderTarget) {
		SDL_DestroyRenderer(renderTarget);
		renderTarget = nullptr;
	}
	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}
}


SDL_Renderer* Window::SetRenderTarget()
{
	if (!window) {
		std::cerr << "Window is not implemented, no renderer will be created" << std::endl;
	}
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	return renderTarget;
}