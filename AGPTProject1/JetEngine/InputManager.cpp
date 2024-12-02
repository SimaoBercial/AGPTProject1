#include "InputManager.h"
#include <iostream>

InputManager::InputManager() : gamepad(nullptr), deadZone(0.2f) {} 

InputManager::~InputManager() {
    if (gamepad) {
        SDL_GameControllerClose(gamepad);
        std::cout << "Gamepad disconnected." << std::endl;
    }
}

bool InputManager::ProcessInput(bool& isRunning) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
    }

    
    int numJoysticks = SDL_NumJoysticks();
  
    if (gamepad == nullptr && numJoysticks > 0) {
        if (SDL_IsGameController(0)) {
            gamepad = SDL_GameControllerOpen(0);
            if (gamepad) {
                std::cout << "Gamepad connected: " << SDL_GameControllerName(gamepad) << std::endl;
            }
            else {
                std::cerr << "SDL_GameControllerOpen Error: " << SDL_GetError() << std::endl;
            }
        }
    }

    return isRunning;
}

const Uint8* InputManager::GetKeyState() const {
    return SDL_GetKeyboardState(nullptr);
}

bool InputManager::IsGamepadConnected() const {
    return gamepad != nullptr;
}

bool InputManager::IsButtonPressed(int button) const {
    if (gamepad) {
        return SDL_GameControllerGetButton(gamepad, static_cast<SDL_GameControllerButton>(button)) == 1;
    }
    return false;
}

float InputManager::GetAxis(int axis) const {
    if (gamepad) {
        float axisValue = SDL_GameControllerGetAxis(gamepad, static_cast<SDL_GameControllerAxis>(axis)) / 32767.0f;
        if (std::abs(axisValue) < deadZone) {
            axisValue = 0.0f;
        }
        return axisValue;
    }
    return 0.0f;
}
