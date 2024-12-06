#ifndef MISSILE_H
#define MISSILE_H

#include "GameObject.h"
#include "SDL.h"
#include "Renderer.h"

class Missile : public GameObject {
public:
    Missile();
    ~Missile();

    void Initialize(SDL_Texture* texture, SDL_Rect startPosition, float speed);
    void Update(float deltaTime, int textureWidth, int textureHeight, int frameWidth, int frameHeigth) override;
    void Render() override;
    SDL_Rect GetBoundingBox() const override;
    bool IsOffScreen() const;

private:
    SDL_Texture* texture;
    SDL_Rect position;
    SDL_Rect spriteRectMissile;
    int frameWidth;
    int frameHeight;
	

    float speed;
};

#endif
