#include "JetEngine.h"
#include <iostream>
#include <SDL.h>
#include "Window.h"

//https://documentation.help/SDL/index.html
//https://stackoverflow.com/questions/21007329/what-is-an-sdl-renderer
//https://wiki.libsdl.org/SDL3/SDL_Event

void JetEngine::start() {
	
	SDL_Init(SDL_INIT_VIDEO);

	Window window;
	bool isRunning = true;
	int initTime = 0;
	int currentTime = 0;
	float deltaTime = 0;
	SDL_Event event;

	SDL_Delay(4000); 

	//GameLoop
	
	while(isRunning){
		initTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - initTime) / 1000.0f;

		//Event Loop
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				isRunning = false;
			}
		}
	}
	SDL_Quit();

}
