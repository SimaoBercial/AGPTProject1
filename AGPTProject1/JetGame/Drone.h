#ifndef DRONE_H
#define DRONE_H

#include "Enemies.h"
//Drones have a horizontal sinusoidal move and appear in packs (see reference video).


class Drone : public Enemies
{
public:
	Drone(SDL_Texture* texture, SDL_Rect position, int textureWidth, int textureHeight);
	~Drone();

	void Update(float deltaTime) override;
	void Render(Renderer* renderer) override;
	SDL_Rect GetBoundingBox() const override;
};

#endif
