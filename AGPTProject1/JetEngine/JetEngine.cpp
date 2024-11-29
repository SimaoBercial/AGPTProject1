#include "JetEngine.h"
#include <iostream>
#include <SDL.h>
#include "Window.h"

//https://documentation.help/SDL/index.html
//https://stackoverflow.com/questions/21007329/what-is-an-sdl-renderer
//https://wiki.libsdl.org/SDL3/SDL_Event
//https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf
//https://www.youtube.com/watch?v=-CIkR1R3a_A - SDL2 Event Handling

void JetEngine::start() {
	
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);

	Window window;
	bool isRunning = true;
	int startTime = 0;
	int currentTime = 0;
	float deltaTime = 0;
	float spriteframesTime = 0;
	
	SDL_Event event;

	SDL_Texture* background = window.LoadTexture("C:\\Users\\Sauchixa\\Desktop\\AGPTProject1\\AGPTProject1\\JetEngine\\graphics\\galaxy2.bmp"); //to be sent from level (i guess)

	//GameLoop
	
	while(isRunning){
		startTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - startTime) / 1000.0f;

				

		//Event Handling
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				isRunning = false;
			}
		}

	}

}
