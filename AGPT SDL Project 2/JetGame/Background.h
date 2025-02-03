#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "SDL.h"
#include "Renderer.h"
#include <vector>

class Background {
public:
    Background();
    ~Background();

    void Initialize(SDL_Texture& backgroundTexture, SDL_Texture& parallaxTexture, float scrollSpeed, int width, int height);
    void Update(float deltaTime);
    void Render(Renderer* renderer);


private:
	float offsetY;
    float scrollSpeed;
    int screenWidth;
    int screenHeight;
	SDL_Rect background;
	SDL_Rect parallax;
    SDL_Rect spriteRect;
    SDL_Texture* backgroundTexture;
    SDL_Texture* parallaxTexture;
};

#endif
