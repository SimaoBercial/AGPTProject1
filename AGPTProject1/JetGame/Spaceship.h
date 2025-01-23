#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Missile.h"
#include "Pawn.h"
#include <vector>
#include <iostream>

class Spaceship : public Pawn{

public:
	Spaceship(SDL_Texture* texture, SDL_Rect position);
	~Spaceship();

	void HandleInput(const Uint8* keyState, float deltaTime, InputManager* inputManager) override;
	void Update(float deltaTime) override;
	void Render(Renderer* renderer) override;
	void CreateRigidBody(Physics* physics) override;
	void GetScreenSize(float screenWidth, float screenHeight);
	void GetMissileTexture(SDL_Texture* missileTexture);

private:
	void UpdateAnimation(float deltaTime);
	void HandleShooting(InputManager* inputManager, float deltaTime);
	float missileTimer;
	float missileCooldown;
	float lifePoints;
	SDL_Texture* missileTexture;
	std::vector <Missile> missiles;


};
#endif