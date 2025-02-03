#ifndef MISSILE_H
#define MISSILE_H

#include "GameObject.h"

class Missile : public GameObject {
public:
    Missile(SDL_Texture* texture, SDL_Rect position);
    ~Missile();

    void Update(float deltaTime) override;
    void Render(Renderer* renderer) override;
    SDL_Rect GetBoundingBox() const override;
	void CreateRigidBody(Physics* physics) override;
    bool IsOffScreen() const;
    int damage;
};

#endif
