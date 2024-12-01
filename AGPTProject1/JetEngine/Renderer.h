#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <SDL.h>

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool Initialize(SDL_Window* window);
    void Shutdown();
    SDL_Texture* LoadTexture(const std::string& filePath);
    void Clear();
    void Render(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect);
    void Present();
    SDL_Renderer* GetSDLRenderer() const;

private:
    SDL_Renderer* renderer;
};

#endif
