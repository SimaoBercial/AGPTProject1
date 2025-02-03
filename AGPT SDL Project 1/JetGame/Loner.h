#ifndef LONER_H
#define LONER_H

#include "Enemies.h"

//This enemy moves horizontally at a certain speed. The loner fires at each 2 second interval a projectile in the Spaceship direction.


class Loner : public Enemies
{
public:
	Loner(SDL_Texture* texture, SDL_Rect position, int textureWidth, int textureHeight);
	~Loner();

	void Update(float deltaTime) override;
	void Render(Renderer* renderer) override;
	SDL_Rect GetBoundingBox() const override;
	void CreateRigidBody(Physics* physics) override;


};

#endif