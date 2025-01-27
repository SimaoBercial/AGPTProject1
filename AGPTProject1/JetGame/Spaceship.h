#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Missile.h"
#include "Companion.h"
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
	void StoreMissileTexture(SDL_Texture* missileTexture);
	void StoreCompanionTexture(SDL_Texture* missileTexture);
	void WeaponPowerUp();
	void ShieldPowerUp();
private:
	void UpdateAnimation(float deltaTime);
	void HandleShooting(InputManager* inputManager, float deltaTime);
	void SpawnCompanion();
	float missileTimer;
	float missileCooldown;
	float lifePoints;
	int weaponPowerUp;
	int maxWeaponPowerUp;
	int companionsNumber;
	int maxCompanionsNumber;
	SDL_Texture* missileTexture;
	SDL_Texture* companionTexture;
	b2BodyId rigidbodyId;
	b2Transform rigidbodyTransform;
	std::vector <Missile> missiles;
	std::vector <Companion> companions;
};
#endif