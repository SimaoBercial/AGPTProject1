#include "InputManager.h"

std::unordered_map<SDL_Keycode, bool> InputManager::keyStates;

void InputManager::Update() {
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    for (auto& key : keyStates) {
        key.second = state[SDL_GetScancodeFromKey(key.first)];
    }
}

bool InputManager::IsKeyPressed(SDL_Keycode key) {
    return keyStates[key];
}

bool InputManager::IsKeyReleased(SDL_Keycode key) {
    return !keyStates[key];
}