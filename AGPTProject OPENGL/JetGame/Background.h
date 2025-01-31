#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Renderer.h"

class Background {
public:
    Background();
    ~Background();

    void Initialize(GLuint backgroundTexture, GLuint parallaxTexture, float scrollSpeed, int width, int height);
    void Update(float deltaTime);
    void Render(Renderer* renderer);

private:
    float scrollSpeed;
    int screenWidth;
    int screenHeight;
    SDL_Rect background;
    SDL_Rect parallax;
    SDL_Rect spriteRect;
    GLuint backgroundTexture;
    GLuint parallaxTexture;
};

#endif // BACKGROUND_H
