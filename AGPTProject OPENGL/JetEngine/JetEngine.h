#ifndef JET_ENGINE_H
#define JET_ENGINE_H

#include <SDL.h>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Renderer.h"
#include "InputManager.h"
#include "Physics.h"

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
    Physics* GetPhysicsEngine();

    SDL_GLContext GetOpenGLContext() const;
    SDL_Window* GetWindow() const;

private:
    SDL_Window* window;
    SDL_GLContext glContext;
    Renderer renderer;
    InputManager inputManager;
    Physics physics;

    Uint32 prevTime, currentTime;
    float deltaTime;
};

#endif // JET_ENGINE_H
