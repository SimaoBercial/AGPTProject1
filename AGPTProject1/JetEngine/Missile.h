#ifndef MISSILE_H
#define MISSILE_H

#include "GameObject.h"
#include "SDL.h"
#include "Renderer.h"
#include <iostream>

class Missile : public GameObject {
public:
    Missile(SDL_Texture* texture, SDL_Rect position);
    ~Missile();

    void Update(float deltaTime) override;
    void Render(Renderer* renderer) override;
    SDL_Rect GetBoundingBox() const override;
	bool IsOffScreen() const;


private:
    int damage;
};

#endif
