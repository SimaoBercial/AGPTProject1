#ifndef RUSHER_H
#define RUSHER_H

#include "Enemies.h"

//This enemy moves vertically at a certain speed.

class Rusher : public Enemies
{
public:
	Rusher(SDL_Texture* texture, SDL_Rect position, int textureWidth, int textureHeight);
	~Rusher();

	void Update(float deltaTime) override;
	void Render(Renderer* renderer) override;
	SDL_Rect GetBoundingBox() const override;
	void CreateRigidBody(Physics* physics) override;

};

#endif