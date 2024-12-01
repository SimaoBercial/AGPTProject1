#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <string>

class Renderer {
public:
    static SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& filePath);
    static void Draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dest);
};

#endif