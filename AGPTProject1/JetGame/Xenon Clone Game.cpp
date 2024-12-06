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
    SDL_Texture* backgroundTexture = engine.GetRenderer()->LoadTexture("graphics/galaxy2.bmp");
    SDL_Texture* parallaxTexture = engine.GetRenderer()->LoadTexture("graphics/Blocks.bmp"); 
    SDL_Texture* missileTexture = engine.GetRenderer()->LoadTexture("graphics/missile.bmp"); //32x48 (16*16 frames in a 2x3 sprite)
	SDL_Texture* rusherTexture = engine.GetRenderer()->LoadTexture("graphics/rusher.bmp"); //256x192  (64*32 frames in a 4x6 sprite )  
	SDL_Texture* lonerTexture = engine.GetRenderer()->LoadTexture("graphics/LonerA.bmp"); // 256*256 (64x64 frames in a 4x4 sprite)  

    Player player;
    player.Initialize(playerTexture, missileTexture, { 320 - 16, 400, 64, 64 });

    Background background;
    background.Initialize(*backgroundTexture, *parallaxTexture ,1.0f, 640, 480 );


    std::vector<Enemy> rushers; //move vertically
    for (int i = 0; i < 5; ++i) {
        Enemy rusher;               
        rusher.Initialize(rusherTexture, { 100 + i * 100, 10, 64, 32 }, 1.0f, 64, 32);//{ enemy x position, enemy y position, sprite Xsize for each frame, sprite Ysize for each frame}
        rushers.push_back(rusher);
    }


	std::vector<Enemy> loners; //move horizontally
	for (int i = 0; i < 5; ++i) {
		Enemy loner;
		loner.Initialize(lonerTexture, { 0 + i * 100, 50, 64, 64 }, 1.0f, 64, 64);//{ enemy x position, enemy y position, sprite Xsize for each frame, sprite Ysize for each frame}
		loners.push_back(loner);
	}

    std::vector<Missile> missiles;

    bool isRunning = true;

    while (engine.ProcessInput(isRunning)) {
        float deltaTime = engine.GetDeltaTime();
        const Uint8* keyState = engine.GetInputManager()->GetKeyState();

        player.HandleInput(keyState, deltaTime, engine.GetInputManager());

        player.Update(deltaTime);

        for (auto& enemy : rushers) {    //256x192  (64*32 frames in a 4x6 sprite )
			enemy.SetEnemy(false, true);
			enemy.Update(deltaTime, 256, 192, 64, 32);
        }
		for (auto& enemy : loners) {     // 256*256 (64x64 frames in a 4x4 sprite) 
			enemy.SetEnemy(true, false);
			enemy.Update(deltaTime, 256, 256, 64, 64);
		}

        for (auto& missile : missiles) { //32x48 (16*16 frames in a 2x3 sprite)
            missile.Update(deltaTime, 32, 48, 16, 16);
        }

        background.Update(deltaTime);

        engine.GetRenderer()->Clear();

        background.Render(engine.GetRenderer());

        player.Render(engine.GetRenderer());

        for (auto& enemy : rushers) {
            enemy.Render();
		}
		for (auto& enemy : loners) {
			enemy.Render();
		}

        engine.GetRenderer()->Present();
    }

    engine.Shutdown();
    return 0;
}
