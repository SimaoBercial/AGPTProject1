#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "SDL.h"

class Enemy : public GameObject {
public:
    Enemy();
    ~Enemy();

    void Initialize(SDL_Texture* texture, SDL_Rect startPosition, float speed);
    void Update(float deltaTime) override;
    void Render() override;

    SDL_Rect GetBoundingBox() const;

private:
    SDL_Texture* texture;
    SDL_Rect position;
    float speed;
};

#endif
