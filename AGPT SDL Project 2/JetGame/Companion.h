#ifndef COMPANION_H
#define COMPANION_H

#include "GameObject.h"
#include "Missile.h"
#include <vector>
//The Space Ship can have up to two companions
//Companions are like “clones” of the spaceship, they also have fire power, can die and get power ups. Basically, they have the 
// same behavior as the Ship, but they are close to the Spaceship.
// When the Spaceship fires, their companions also fire. When the Spaceship dies, the companions also die.

class Companion: public GameObject
{
public:
	Companion(SDL_Texture* texture, SDL_Rect position, int textureWidth, int textureHeight);
	~Companion();
	void Movement(float deltaTime);
	void Update(float deltaTime) override;
	void Render(Renderer* renderer) override;
	SDL_Rect GetBoundingBox() const override;
	void CreateRigidBody(Physics* physics) override;
	void ShootMissile(SDL_Texture* missileTexture);
	bool movingLeft;
	bool movingRight;
	bool movingUp;
	bool movingDown;
	float velocityX; //speed on X
	float velocityY; //speed on Y
	float screenHeight;
	float screenWidth;

private:
	void UpdateAnimation(float deltaTime);
	void WeaponPowerUp();
	void ShieldPowerUp();

	int maxWeaponPowerUp;
	int weaponPowerUp;
	float lifePoints;
	float missileTimer;
	float moveSpeed;
	float missileCooldown;
	b2ShapeId rigidbodyId;
	b2Transform rigidbodyTransform;
	std::vector <Missile> missiles;
	SDL_Texture* missileTexture;
	Physics* physics;
};

#endif