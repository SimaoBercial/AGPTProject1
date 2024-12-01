#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

class Player {
public:
    Player(SDL_Renderer* renderer);
    void HandleInput();
    void Update();
    void Render(SDL_Renderer* renderer);

private:
    SDL_Texture* texture;
    SDL_Rect position;
};

#endif
