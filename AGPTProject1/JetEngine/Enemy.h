#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "Renderer.h"
#include "SDL.h"

class Enemy : public GameObject {
public:
    Enemy();
    ~Enemy();

    void Initialize(SDL_Texture* texture, SDL_Rect startPosition, float speed);
    void Update(float deltaTime, int textureWidth, int textureHeight, int frameWidth, int frameHeigth) override;
    void Render() override;

    SDL_Rect GetBoundingBox() const;

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect position;
    SDL_Rect frameRect; //the frame the sprite is at
    float speed;
};

#endif
