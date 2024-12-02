#pragma once
#include <SDL.h>
#include <vector>
#include "InputManager.h"
#include "Renderer.h"
#include "Missile.h"

class Player {
public:
    Player();
    ~Player();

    void Initialize(SDL_Texture* playerTexture, SDL_Texture* missileTexture, const SDL_Rect& startPosition = { 0, 0, 32, 32 });
    void HandleInput(const Uint8* keyState, float deltaTime, InputManager* inputManager);
    void Update(float deltaTime);
    void Render(Renderer* renderer);

private:
    SDL_Texture* texture;
    SDL_Rect position;
    SDL_Rect spriteRect; 
    float moveSpeed;
    int currentFrame;     
    float frameTime;      
    const int numFrames;  
    const int frameWidth; 
    const int frameHeight; 

    bool movingLeft;
    bool movingRight;

    SDL_Texture* missileTexture;    
    float missileCooldown;          
    float missileTimer;             
    std::vector<Missile> missiles;  

    void UpdateAnimation(float deltaTime);
    void HandleShooting(InputManager* inputManager, float deltaTime);
};
