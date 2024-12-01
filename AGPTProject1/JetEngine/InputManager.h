#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>
#include <unordered_map>

class InputManager {
public:
    static void Update();
    static bool IsKeyPressed(SDL_Keycode key);
    static bool IsKeyReleased(SDL_Keycode key);

private:
    static std::unordered_map<SDL_Keycode, bool> keyStates;
};

#endif