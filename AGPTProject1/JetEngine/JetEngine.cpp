#include "JetEngine.h"
#include <iostream>
#include <SDL.h>
#include "Window.h"

void JetEngine::start() {
	
	SDL_Init(SDL_INIT_VIDEO);

	Window window;

	std::cout << "Engine started!!!" << std::endl;
}
