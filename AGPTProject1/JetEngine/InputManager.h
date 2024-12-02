#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>

class InputManager {
public:
    InputManager();
    ~InputManager();

    bool ProcessInput(bool& isRunning);
    const Uint8* GetKeyState() const;

    bool IsGamepadConnected() const;
    bool IsButtonPressed(int button) const;
    float GetAxis(int axis) const;

private:
    SDL_Event event;
    SDL_GameController* gamepad;
    float deadZone;
};

#endif
