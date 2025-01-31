#include "JetEngine.h"
#include "Spaceship.h"
#include "Drone.h"
#include "Loner.h"
#include "Rusher.h"
#include "Background.h"
#include <iostream>
#include "Missile.h"
#include "Shader.h"
#include "Renderer.h"
#include <glad/glad.h>
#include <SDL.h>

int main(int argc, char** argv) {
    int screenWidth = 640;
    int screenHeight = 480;

    JetEngine engine;
    if (!engine.Initialize("Xenon Clone Game", screenWidth, screenHeight)) {
        return -1;
    }

    SDL_GLContext context = engine.GetOpenGLContext();
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return -1;
    }

    Renderer* renderer = engine.GetRenderer();

    GLuint backgroundTexture = renderer->LoadTexture("graphics/galaxy2.bmp");
    GLuint parallaxTexture = renderer->LoadTexture("graphics/Blocks.bmp");
    GLuint spaceshipTexture = renderer->LoadTexture("graphics/Ship1.bmp");
    GLuint missileTexture = renderer->LoadTexture("graphics/missile.bmp");
    GLuint rusherTexture = renderer->LoadTexture("graphics/rusher.bmp");
    GLuint lonerTexture = renderer->LoadTexture("graphics/LonerA.bmp");
    GLuint droneTexture = renderer->LoadTexture("graphics/Drone.bmp");
    GLuint projectilesTexture = renderer->LoadTexture("graphics/EnWeap6.bmp");
    GLuint companionTexture = renderer->LoadTexture("graphics/clone.bmp");
    GLuint explosionTexture = renderer->LoadTexture("graphics/explode16.bmp");
    GLuint shieldPowerTexture = renderer->LoadTexture("graphics/PUShield.bmp");
    GLuint weaponPowerUpTexture = renderer->LoadTexture("graphics/PUWeapon.bmp");
    GLuint stoneBigAsteroidsTexture = renderer->LoadTexture("graphics/SAster96.bmp");
    GLuint stoneMidAsteroidsTexture = renderer->LoadTexture("graphics/SAster64.bmp");
    GLuint stoneSmallAsteroidsTexture = renderer->LoadTexture("graphics/SAster32.bmp");
    GLuint metalBigAsteroidsTexture = renderer->LoadTexture("graphics/MAster96.bmp");
    GLuint metalMidAsteroidsTexture = renderer->LoadTexture("graphics/MAster64.bmp");
    GLuint metalSmallAsteroidsTexture = renderer->LoadTexture("graphics/MAster32.bmp");

    Physics* physics = engine.GetPhysicsEngine();
    physics->SetRenderer(renderer);

    b2WorldId worldId = physics->GetWorld();
    std::cout << "The world ID is: " << &worldId << std::endl;

    Background background;
    background.Initialize(parallaxTexture, backgroundTexture, 1.0f, screenWidth, screenHeight);

    Spaceship spaceship(spaceshipTexture, { 304, 400, 64, 64 });
    spaceship.GetScreenSize(screenWidth, screenHeight);
    spaceship.StoreMissileTexture(missileTexture);
    spaceship.StoreCompanionTexture(companionTexture);
    spaceship.CreateRigidBody(physics);

    std::vector<Drone> drones;
    for (int i = 0; i < 8; ++i) {
        Drone drone(droneTexture, { 100, 10 + i * 32, 32, 32 }, 256, 640);
        drones.push_back(drone);
        drone.CreateRigidBody(engine.GetPhysicsEngine());
    }

    std::vector<Loner> loners;
    for (int i = 0; i < 5; ++i) {
        Loner loner(lonerTexture, { 0 + i * 100, 50, 64, 64 }, 256, 256);
        loners.push_back(loner);
        loner.CreateRigidBody(engine.GetPhysicsEngine());
    }

    std::vector<Rusher> rushers;
    for (int i = 0; i < 5; ++i) {
        Rusher rusher(rusherTexture, { 0 + i * 100, 150, 64, 32 }, 256, 192);
        rushers.push_back(rusher);
        rusher.CreateRigidBody(engine.GetPhysicsEngine());
    }

    bool isRunning = true;

    while (engine.ProcessInput(isRunning)) {
        // Get DeltaTime and Input State
        float deltaTime = engine.GetDeltaTime();
        const Uint8* keyState = engine.GetInputManager()->GetKeyState();
        spaceship.HandleInput(keyState, deltaTime, engine.GetInputManager());

        // Update physics and game objects
        physics->UpdatePhysics();
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

        // Clear screen before rendering
        renderer->Clear();

        // Render background and objects
        background.Render(renderer);
        spaceship.Render(renderer);

        for (auto& rusher : rushers) {
            rusher.Render(renderer);
        }
        for (auto& loner : loners) {
            loner.Render(renderer);
        }
        for (auto& drone : drones) {
            drone.Render(renderer);
        }

        renderer->Present(engine.GetWindow());
    }

    engine.Shutdown();
    return 0;
}
