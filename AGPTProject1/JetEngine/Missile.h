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
    void Update(float deltaTime) override;
    void Render() override;
    SDL_Rect GetBoundingBox() const override;
    bool IsOffScreen() const;

private:
    SDL_Texture* texture;
    SDL_Rect position;
    float speed;
};

#endif
