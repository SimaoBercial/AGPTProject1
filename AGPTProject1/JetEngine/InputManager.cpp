#include "InputManager.h"
#include <iostream>

InputManager::InputManager() : gamepad(nullptr) {}

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
    if (gamepad == nullptr && SDL_NumJoysticks() > 0) {
        gamepad = SDL_GameControllerOpen(0);
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
        return axisValue;
    }
    return 0.0f;
}
