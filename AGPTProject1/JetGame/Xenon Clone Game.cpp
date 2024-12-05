#include "JetEngine.h"
#include <iostream>
#include <cmath>
#include "Background.h"

int main(int argc, char** argv) {
    JetEngine engine;
    if (!engine.Initialize("SDL2 Engine Game", 640, 480)) {
        return -1;
    }


    SDL_Texture* playerTexture = engine.GetRenderer()->LoadTexture("graphics/Ship1.bmp");
    SDL_Texture* backgroundLayer1Texture = engine.GetRenderer()->LoadTexture("graphics/galaxy2.bmp");
    SDL_Texture* backgroundLayer2Texture = engine.GetRenderer()->LoadTexture("graphics/clone.bmp"); 
    SDL_Texture* missileTexture = engine.GetRenderer()->LoadTexture("graphics/missile.bmp");
    SDL_Texture* enemyTexture = engine.GetRenderer()->LoadTexture("graphics/drone.bmp");

    Player player;
    player.Initialize(playerTexture, missileTexture, { 320 - 16, 400, 64, 64 });

    Background background;
    background.Initialize({ backgroundLayer1Texture, backgroundLayer2Texture },{ 0.0f, 20.0f }, 640, 480 );


    std::vector<Enemy> enemies;
    for (int i = 0; i < 5; ++i) {
        Enemy enemy;
        enemy.Initialize(enemyTexture, { 100 + i * 100, 50, 32, 32 }, 100.0f);
        enemies.push_back(enemy);
    }

    std::vector<Missile> missiles;

    bool isRunning = true;

    while (engine.ProcessInput(isRunning)) {
        float deltaTime = engine.GetDeltaTime();
        const Uint8* keyState = engine.GetInputManager()->GetKeyState();

        player.HandleInput(keyState, deltaTime, engine.GetInputManager());

        player.Update(deltaTime);

        for (auto& enemy : enemies) {
            enemy.Update(deltaTime);
        }

        for (auto& missile : missiles) {
            missile.Update(deltaTime);
        }

        background.Update(deltaTime);

        engine.GetRenderer()->Clear();

        background.Render(engine.GetRenderer());

        player.Render(engine.GetRenderer());

        for (auto& enemy : enemies) {
            enemy.Render();
        }

        engine.GetRenderer()->Present();
    }

    engine.Shutdown();
    return 0;
}
