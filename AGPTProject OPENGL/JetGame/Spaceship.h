#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Missile.h"
#include "Companion.h"
#include "Pawn.h"
#include <vector>
#include <iostream>

class Spaceship : public Pawn {
public:
    Spaceship(GLuint texture, SDL_Rect position);
    ~Spaceship();

    void HandleInput(const Uint8* keyState, float deltaTime, InputManager* inputManager) override;
    void Update(float deltaTime) override;
    void Render(Renderer* renderer) override;
    void CreateRigidBody(Physics* physics) override;
    void GetScreenSize(float screenWidth, float screenHeight);
    void StoreMissileTexture(GLuint missileTexture);
    void StoreCompanionTexture(GLuint companionTexture);
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

    GLuint texture;
    GLuint missileTexture;
    GLuint companionTexture;

    b2ShapeId rigidbodyId;
    b2Transform rigidbodyTransform;

    std::vector<Missile> missiles;
    std::vector<Companion> companions;

    Physics* physics;
};

#endif // SPACESHIP_H
