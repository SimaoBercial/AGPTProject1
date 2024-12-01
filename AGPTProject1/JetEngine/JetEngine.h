#ifndef JETENGINE_H
#define JETENGINE_H

#include "Renderer.h"
#include "InputManager.h"

class JetEngine {
public:
    JetEngine();
    ~JetEngine();

    bool Initialize(const std::string& windowTitle, int width, int height);
    void Shutdown();
    float GetDeltaTime();
    bool ProcessInput(bool& isRunning);

    Renderer* GetRenderer();
    InputManager* GetInputManager();

private:
    SDL_Window* window;
    int prevTime;
    int currentTime;
    float deltaTime;

    Renderer renderer;
    InputManager inputManager;
};

#endif
