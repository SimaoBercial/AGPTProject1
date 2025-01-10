#ifndef JETENGINE_H
#define JETENGINE_H

#include <string>
#include "Renderer.h"
#include "InputManager.h"
#include "Pawn.h"
#include "Missile.h"
#include "Enemy.h"
#include <vector>

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
    Uint32 prevTime, currentTime;
    float deltaTime;

    Renderer renderer;
    InputManager inputManager;
    

   // std::vector<Enemy> enemies;  // Store enemies in a vector
};

#endif
