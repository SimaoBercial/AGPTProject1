#include "Renderer.h"
#include <iostream>

Renderer::Renderer() : renderer(nullptr) {}

Renderer::~Renderer() {
    Shutdown();
}

bool Renderer::Initialize(SDL_Window* window) {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void Renderer::Shutdown() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
}

SDL_Texture* Renderer::LoadTexture(const std::string& filePath) {
    SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
    if (!surface) {
        std::cerr << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    }

    return texture;
}

void Renderer::Clear() {
    SDL_RenderClear(renderer);
}

void Renderer::Render(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect) {
    SDL_RenderCopy(renderer, texture, srcRect, dstRect);
}

void Renderer::Present() {
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Renderer::GetSDLRenderer() const {
    return renderer;
}
