#include "JetEngine.h"
#include <iostream>
#include <SDL.h>


JetEngine::JetEngine(const std::string& title, int width, int height)
    : running(true), window(nullptr), renderer(nullptr) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL Initialization Error: " << SDL_GetError() << std::endl;
        running = false;
        return;
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window Creation Error: " << SDL_GetError() << std::endl;
        running = false;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer Creation Error: " << SDL_GetError() << std::endl;
        running = false;
        return;
    }
}

JetEngine::~JetEngine() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void JetEngine::Run() {
    while (running) {
        ProcessEvents();
        Update();
        Render();
    }
}

void JetEngine::Quit() {
    running = false;
}

void JetEngine::ProcessEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            Quit();
        }
    }
}

void JetEngine::Update() {
    // Update game logic here
}

void JetEngine::Render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render game objects here

    SDL_RenderPresent(renderer);
}
