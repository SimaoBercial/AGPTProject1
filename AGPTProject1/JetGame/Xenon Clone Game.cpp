#include "JetEngine.h"
#include "iostream"

int main(int argc, char** argv) {
    JetEngine engine;
    if (!engine.Initialize("SDL2 Engine Game", 640, 480)) {
        return -1;
    }

    SDL_Texture* playerTexture = engine.GetRenderer()->LoadTexture("graphics/drone.bmp");
    SDL_Texture* backgroundTexture = engine.GetRenderer()->LoadTexture("graphics/galaxy2.bmp");

    SDL_Rect playerRect = { 0, 0, 32, 32 };
    SDL_Rect playerPosition = { 0, 0, 32, 32 };

    float moveSpeed = 200.0f;
    float frameTime = 0.0f;
    int frameWidth = 32;
    int frameHeight = 32;
    bool isRunning = true;

    while (engine.ProcessInput(isRunning)) {
        float deltaTime = engine.GetDeltaTime();

        const Uint8* keyState = engine.GetInputManager()->GetKeyState();

        // Handle keyboard movement
        if (keyState[SDL_SCANCODE_D] || engine.GetInputManager()->IsButtonPressed(SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
            playerPosition.x += moveSpeed * deltaTime;
        }
        if (keyState[SDL_SCANCODE_A] || engine.GetInputManager()->IsButtonPressed(SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
            playerPosition.x -= moveSpeed * deltaTime;
        }
        if (keyState[SDL_SCANCODE_S] || engine.GetInputManager()->IsButtonPressed(SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
            playerPosition.y += moveSpeed * deltaTime;
        }
        if (keyState[SDL_SCANCODE_W] || engine.GetInputManager()->IsButtonPressed(SDL_CONTROLLER_BUTTON_DPAD_UP)) {
            playerPosition.y -= moveSpeed * deltaTime;
        }

        // Handle gamepad axis movement
        float gamepadX = engine.GetInputManager()->GetAxis(SDL_CONTROLLER_AXIS_LEFTX);
        float gamepadY = engine.GetInputManager()->GetAxis(SDL_CONTROLLER_AXIS_LEFTY);

        // Apply gamepad movement if the gamepad is connected
        if (engine.GetInputManager()->IsGamepadConnected()) {
            playerPosition.x += gamepadX * moveSpeed * deltaTime;
            playerPosition.y += gamepadY * moveSpeed * deltaTime;
        }

        frameTime += deltaTime;
        if (frameTime >= 0.05f) {
            frameTime = 0;
            playerRect.x += frameWidth;
            if (playerRect.x >= 256) {
                playerRect.x = 0;
                playerRect.y += frameHeight;
                if (playerRect.y >= 64) {
                    playerRect.y = 0;
                }
            }
        }

        engine.GetRenderer()->Clear();
        engine.GetRenderer()->Render(backgroundTexture, nullptr, nullptr);
        engine.GetRenderer()->Render(playerTexture, &playerRect, &playerPosition);
        engine.GetRenderer()->Present();
    }

    engine.Shutdown();
    return 0;
}
