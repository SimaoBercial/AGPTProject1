#include "Renderer.h"
#include <iostream>

SDL_Texture* Renderer::LoadTexture(SDL_Renderer* renderer, const std::string& filePath) {
    SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
    if (!surface) {
        std::cerr << "Failed to load BMP: " << filePath << " Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Failed to create texture from BMP: " << SDL_GetError() << std::endl;
    }

    return texture;
}

void Renderer::Draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dest) {
    SDL_RenderCopy(renderer, texture, src, dest);
}
