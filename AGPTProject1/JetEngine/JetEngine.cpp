#include "JetEngine.h"
#include <SDL.h>
#include <iostream>

JetEngine::JetEngine() : window(nullptr), prevTime(0), currentTime(0), deltaTime(0.0f) {}

JetEngine::~JetEngine() {
    Shutdown();
}

bool JetEngine::Initialize(const std::string& windowTitle, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!renderer.Initialize(window)) {
        return false;
    }
    return true;
}

void JetEngine::Shutdown() {
    renderer.Shutdown();
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

float JetEngine::GetDeltaTime() {
    prevTime = currentTime;
    currentTime = SDL_GetTicks();
    deltaTime = (currentTime - prevTime) / 1000.0f;
    return deltaTime;
}

bool JetEngine::ProcessInput(bool& isRunning) {
    return inputManager.ProcessInput(isRunning);
}

Renderer* JetEngine::GetRenderer() {
    return &renderer;
}

InputManager* JetEngine::GetInputManager() {
    return &inputManager;
}
