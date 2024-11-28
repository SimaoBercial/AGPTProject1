#include <iostream>
#include <SDL.h>

SDL_Texture* LoadTexture(std::string filePath, SDL_Renderer* renderTarget)
{
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
    if (surface == NULL)
        std::cout << "Error" << std::endl;
    else
    {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
        texture = SDL_CreateTextureFromSurface(renderTarget, surface);
        if (texture == NULL)
            std::cout << "Error" << std::endl;
    }

    SDL_FreeSurface(surface);

    return texture;
}

int main(int argc, char** argv)
{

    SDL_Window* window = nullptr;
    SDL_Texture* currentImage = nullptr;
    SDL_Renderer* renderTarget = nullptr;
    SDL_Texture* background = nullptr;
    int textureWidth = 0;
    int textureHeight = 0;
    int frameWidth = 0;
    int frameHeight = 0;

    float moveSpeed = 200.0f;
    const Uint8* keyState;

    SDL_Rect playerPosition;
    playerPosition.x = playerPosition.y = 0;
    playerPosition.w = playerPosition.h = 32;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL2 Demo!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);

   renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    currentImage = LoadTexture("graphics/drone.bmp", renderTarget);
    background = LoadTexture("graphics/galaxy2.bmp", renderTarget);
    SDL_QueryTexture(currentImage, NULL, NULL, &textureWidth, &textureHeight);


    frameWidth = textureWidth / 8; 
    frameHeight = textureHeight / 2;

    SDL_Rect playerRect;
    playerRect.x = playerRect.y = 0;
    playerRect.w = frameWidth;
    playerRect.h = frameHeight;

    

    float frameTime = 0; ////time that the animation of the sprite takes for each sprite frame.
    int prevTime = 0;
    int currentTime = 0;
    float deltaTime = 0;

    
    bool isRunning = true;
    SDL_Event ev;

    //Game Loop
    while (isRunning) 
    {
        prevTime = currentTime;
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - prevTime) / 1000.0f;

        //Event Loop
        while (SDL_PollEvent(&ev) != 0)
        {
            if (ev.type == SDL_QUIT)
                isRunning = false;
            
        }

        keyState = SDL_GetKeyboardState(NULL);
        if (keyState[SDL_SCANCODE_D])
            playerPosition.x += moveSpeed * deltaTime;
        if (keyState[SDL_SCANCODE_A])
            playerPosition.x -= moveSpeed * deltaTime;
        if (keyState[SDL_SCANCODE_S])
            playerPosition.y += moveSpeed * deltaTime;
        if (keyState[SDL_SCANCODE_W])
            playerPosition.y -= moveSpeed * deltaTime;


        frameTime += deltaTime;
        
        if (frameTime >= 0.05f)
        {
            frameTime = 0;
            playerRect.x += frameWidth;
            if (playerRect.x >= textureWidth) {
                playerRect.x = 0;
                playerRect.y += frameHeight;
                if (playerRect.y >= textureHeight) {
                    playerRect.y = 0;
                }
            }
        }


        SDL_RenderClear(renderTarget);
        SDL_RenderCopy(renderTarget, background, NULL, NULL);
        SDL_RenderCopy(renderTarget, currentImage, &playerRect, &playerPosition);
        SDL_RenderPresent(renderTarget);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyTexture(currentImage);
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderTarget);
    window = nullptr;
    currentImage = nullptr;
    renderTarget = nullptr;
    background = nullptr;

    SDL_Quit();
    return 0;
}
