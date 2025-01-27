#include "JetEngine.h"
#include "Spaceship.h"
#include "Drone.h"
#include "Loner.h"
#include "Rusher.h"
#include "Background.h"
#include <iostream>
#include "Missile.h"

int main(int argc, char** argv) {
    int screenWidth = 640;
    int screenHeigth = 480;

    JetEngine engine; //instantiates the engine
    if (!engine.Initialize("SDL2 Engine Game", screenWidth, screenHeigth)) {
        return -1;
    }


    SDL_Texture* backgroundTexture = engine.GetRenderer()->LoadTexture("graphics/galaxy2.bmp");
    SDL_Texture* parallaxTexture = engine.GetRenderer()->LoadTexture("graphics/Blocks.bmp"); 
	SDL_Texture* spaceshipTexture = engine.GetRenderer()->LoadTexture("graphics/Ship1.bmp"); //448x64 (64x64 frames in a 7x1 sprite)
    SDL_Texture* missileTexture = engine.GetRenderer()->LoadTexture("graphics/missile.bmp"); //32x48 (16*16 frames in a 2x3 sprite)
	SDL_Texture* rusherTexture = engine.GetRenderer()->LoadTexture("graphics/rusher.bmp"); //256x192  (64*32 frames in a 4x6 sprite)  
	SDL_Texture* lonerTexture = engine.GetRenderer()->LoadTexture("graphics/LonerA.bmp"); //256x256 (64x64 frames in a 4x4 sprite) 
    SDL_Texture* droneTexture = engine.GetRenderer()->LoadTexture("graphics/Drone.bmp"); //256x64 (32x32 frames in 8x2 sprite)
    SDL_Texture* projectilesTexture = engine.GetRenderer()->LoadTexture("graphics/EnWeap6.bmp"); //128x16 (frames in 8x1 sprite)
    SDL_Texture* companionTexture = engine.GetRenderer()->LoadTexture("graphics/clone.bmp"); //128x160 (32x32 frames in 4x5 sprite)
    SDL_Texture* explosionTexture = engine.GetRenderer()->LoadTexture("graphics/explode16.bmp"); //80x32 (16x16 frames in 5x2 sprite)
    SDL_Texture* shieldPowerTexture = engine.GetRenderer()->LoadTexture("graphics/PUShield.bmp.bmp"); //128x64 (32x32 frames in 5x2 sprite)
    SDL_Texture* weaponPowerUpTexture = engine.GetRenderer()->LoadTexture("graphics/PUWeapon.bmp"); //128x64 (32x32 frames in 5x2 sprite)
	SDL_Texture* stoneBigAsteroidsTexture = engine.GetRenderer()->LoadTexture("graphics/SAster96.bmp"); //480x480 (96x96 frames in a 5x5 sprite)
	SDL_Texture* stoneMidAsteroidsTexture = engine.GetRenderer()->LoadTexture("graphics/SAster64.bmp"); //512x192 (64x64 frames in 8x3 sprite)
	SDL_Texture* stoneSmallAsteroidsTexture = engine.GetRenderer()->LoadTexture("graphics/SAster32.bmp"); //256x64 (32x32 frames in a 8x2 sprite)
	SDL_Texture* metalBigAsteroidsTexture = engine.GetRenderer()->LoadTexture("graphics/MAster96.bmp"); //480x480 (96x96 frames in a 5x5 sprite)
	SDL_Texture* metalMidAsteroidsTexture = engine.GetRenderer()->LoadTexture("graphics/MAster64.bmp"); //512x192 (64x64 frames in 8x3 sprite)
	SDL_Texture* metalSmallAsteroidsTexture = engine.GetRenderer()->LoadTexture("graphics/MAster32.bmp"); //256x64 (32x32 frames in a 8x2 sprite)

	Background background;
	background.Initialize(*backgroundTexture, *parallaxTexture, 1.0f, 640, 480);

	Spaceship spaceship(spaceshipTexture, { 304, 400, 64, 64 }); //instantiates the spaceship/player class for the first time
	spaceship.GetScreenSize(screenWidth, screenHeigth);
	spaceship.StoreMissileTexture(missileTexture);
    spaceship.StoreCompanionTexture(companionTexture);
    spaceship.CreateRigidBody(engine.GetPhysicsEngine());
   
    std::vector<Drone> drones; //Drones have a vertical movement, showing horizontal sinusoidal move and appear in packs of 8(see reference video)
    for (int i = 0; i < 8; ++i) {
        Drone drone(droneTexture, { 100 , 10 + i * 32, 32, 32 }, 256, 640);
		drones.push_back(drone);
        drone.CreateRigidBody(engine.GetPhysicsEngine());
    }

	std::vector<Loner> loners; //This enemy moves horizontally at a certain speed. The loner fires at each 2 second interval a projectile in the Spaceship direction
	for (int i = 0; i < 5; ++i) {
        Loner loner(lonerTexture, { 0 + i * 100, 50, 64, 64 }, 256, 256);
		loners.push_back(loner);
        loner.CreateRigidBody(engine.GetPhysicsEngine());
	}

	std::vector<Rusher> rushers; //This enemy moves vertically at a certain speed
	for (int i = 0; i < 5; ++i) {
		Rusher rusher(rusherTexture, { 0 + i * 100, 150, 64, 32 }, 256, 192);
		rushers.push_back(rusher);
        rusher.CreateRigidBody(engine.GetPhysicsEngine());
	}

    bool isRunning = true;

    while (engine.ProcessInput(isRunning)) {
        float deltaTime = engine.GetDeltaTime();
        const Uint8* keyState = engine.GetInputManager()->GetKeyState();

        spaceship.HandleInput(keyState, deltaTime, engine.GetInputManager());

        spaceship.Update(deltaTime);


        for (auto& rusher : rushers) {    
 			rusher.Update(deltaTime);
        }
		for (auto& loner : loners) {     
 			loner.Update(deltaTime);
 		}
        for (auto& drone : drones) {
            drone.Update(deltaTime);
        }         

        background.Update(deltaTime);

        engine.GetRenderer()->Clear();

        background.Render(engine.GetRenderer());

		spaceship.Render(engine.GetRenderer());

        for (auto& Rusher : rushers) {
            Rusher.Render(engine.GetRenderer());
		}
		for (auto& Loner : loners) {
			Loner.Render(engine.GetRenderer());
 		}
		for (auto& Drone : drones) {
			Drone.Render(engine.GetRenderer());
		}

        engine.GetRenderer()->Present();
    }

    engine.Shutdown();
    return 0;
}
