#ifndef PAWN_H
#define PAWN_H

#include <SDL.h>
#include "InputManager.h"
#include "Renderer.h"

class Pawn {
public:
	virtual ~Pawn() {};

	virtual void HandleInput(const Uint8* keyState, float deltaTime, InputManager* inputManager) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(Renderer* renderer) = 0;;

protected:
	SDL_Texture* texture;
	SDL_Rect position; //the space on the screen where the player is rendered
	SDL_Rect spriteRectPlayer; //the bit of the source texture that is rendered. NULL for the entire texture
	int numFrames; //number of frames the sprite sheet has
	int frameHeight; //the individual frame height
	int frameWidth; //the individual frame width
	int screenWidth;
	int screenHeight; 
	int currentFrame; // the frame the animation is at
	float moveSpeed; // the speed defined by the player on the player actor
	float frameTime; // the time each frames lasts
	float movementMagnitude; // normalized speed
	float posX; //pass to render and collision
	float posY; //pass to render and collision
	float velocityX; //speed on X
	float velocityY; //speed on Y


	bool movingLeft;
	bool movingRight;
	bool movingUp;
	bool movingDown;
};

#endif