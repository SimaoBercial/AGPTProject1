#pragma once

#ifndef JETENGINE_H
#define JETENGINE_H

#include <SDL.h>
#include <string>

class JetEngine {
public:
    JetEngine(const std::string& title, int width, int height);
    ~JetEngine();

    void Run();
    void Quit();

    bool IsRunning() const { return running; }
    SDL_Renderer* GetRenderer() const { return renderer; }

private:
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;

    void ProcessEvents();
    void Update();
    void Render();
};

#endif