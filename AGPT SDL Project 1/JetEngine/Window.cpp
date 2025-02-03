#include "Window.h"
#include "SDL.h"
#include <iostream>

Window::Window() {
	window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
	SetRenderTarget();
}

Window::~Window()
 {
	if (renderTarget) {
		SDL_DestroyRenderer(renderTarget);
		renderTarget = nullptr;
	}
	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}
	SDL_Quit();
}

SDL_Renderer* Window::SetRenderTarget()
{
	if (!window) {
		std::cerr << "Window is not implemented, no renderer will be created" << std::endl;
	}
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	return renderTarget;
}


//perhaps the loading of the textures can be part of the class Level, since it is part of the level and not the window,per say

SDL_Texture* Window::LoadTexture(std::string filePath)
{
	std::cerr << filePath << SDL_GetError() << std::endl;
	surface = SDL_LoadBMP(filePath.c_str());
	if (surface == NULL) {
		std::cerr << "Error - no surface found" << SDL_GetError() << std::endl;
	}
	if (renderTarget == NULL)
	{
		std::cerr << "Error - no render target found" << SDL_GetError() << std::endl;
	}
	else {
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL) std::cerr << "Error - no texture found" << SDL_GetError()<<std::endl;
	}
	SDL_FreeSurface(surface);
	return texture;
}
