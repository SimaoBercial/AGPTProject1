#include "Spaceship.h"


Spaceship::Spaceship(SDL_Texture* texture, SDL_Rect position) : 
missileTimer(0.0f),
missileCooldown(0.2f),
lifePoints(100),
missileTexture(nullptr),
rigidbodyId(b2_nullShapeId),
rigidbodyTransform(b2Transform_identity),
missiles{},
physics(nullptr)
{ 
	this->texture = texture;
	this->position = position; //start position of the sprite, on the screen

	this->frameWidth = 64; //for SDL_Rect w (x,y,w,h)
	this->frameHeight = 64; //for SDL_Rect h (x,y,w,h)
	this->spriteRectPlayer = { 0, 0, frameWidth, frameHeight }; //defaults to the first frame of the sprite

	this->posX = position.x;
	this->posY = position.y;

	this->frameTime = 0.0f;
	this->numFrames = 7;
	this->currentFrame = 3;

	this->moveSpeed = 200.0f;
	this->velocityX = 0.0f;
	this->velocityY = 0.0f;

	this->movingLeft = false;
	this->movingRight = false;
	this->movingUp = false;
	this->movingDown = false;
}

void Spaceship::GetScreenSize(float screenWidth, float screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	
}

void Spaceship::StoreMissileTexture(SDL_Texture* missileTexture) {
	this->missileTexture = missileTexture;
}



void Spaceship::HandleInput(const Uint8* keyState, float deltaTime, InputManager* inputManager)
{
	float velocityX = 0.0f;
	float velocityY = 0.0f;
	
	if (keyState[SDL_SCANCODE_D]) {
		velocityX += 1.0f; //adds 1 to the X axis, then sped up with moveSpeed, updating the pos.X and passing it to the renderer.
		movingLeft = false;
		movingRight = true;
		
	}
	if (keyState[SDL_SCANCODE_A]) {
		velocityX -= 1.0f; //subtracts 1 to the X axis, then sped up with moveSpeed, updating the pos.X and passing it to the renderer.
		movingLeft = true;
		movingRight = false;
		
	}
	if (keyState[SDL_SCANCODE_W]) {
		velocityY -= 1.0f; //adds 1 to the Y axis, then sped up with moveSpeed, updating the pos.Y and passing it to the renderer.
		movingUp = true;
		movingDown = false;
		
	}
	if (keyState[SDL_SCANCODE_S]) {
		velocityY += 1.0f; //subtracts 1 to the Y axis, then sped up with moveSpeed, updating the pos.Y and passing it to the renderer.
		movingUp = false;
		movingDown = true;
		
	}


	if (inputManager->IsGamepadConnected()) {
		float axisX = inputManager->GetAxis(SDL_CONTROLLER_AXIS_LEFTX);
		float axisY = inputManager->GetAxis(SDL_CONTROLLER_AXIS_LEFTY);

		velocityX += axisX;
		velocityY += axisY;
		

		if (axisX > 0.1f) {
			movingLeft = false;
			movingRight = true;
			
		}
		else if (axisX < -0.1f) {
			movingLeft = true;
			movingRight = false;
			
		}
		if (axisY > 0.1f) {
			movingUp = false;
			movingDown = true;
		}
		else if (axisY < -0.1f) {
			movingUp = true;
			movingDown = false;
		}
	}

	movementMagnitude = std::sqrt(velocityX * velocityX + velocityY * velocityY); //normalize diagonal movement
	if (movementMagnitude > 0.0f) {
		velocityX /= movementMagnitude;
		velocityY /= movementMagnitude;
	}
	//calculates the movement speed with precision, using float point precision
	posX += velocityX * moveSpeed * deltaTime;
	posY += velocityY * moveSpeed * deltaTime;

	//takes the movement precision value, then rounds up, 
	//converting and rounding the float to an integer, 
	//for the rendering of SDL_Rect
	position.x = static_cast<int>(posX);
	position.y = static_cast<int>(posY);

	if (position.x < 0) position.x = 0;
	if (position.y < 0) position.y = 0;
	if (position.x + position.w > screenWidth) position.x = screenWidth - position.w; //cant go off the borders of the screen on X axis
	if (position.y + position.h > screenHeight) position.y = screenHeight - position.h; //cant go off the borders of the screen on Y axis

	if (velocityX == 0.0f && velocityY == 0.0f) {
		movingLeft = false;
		movingRight = false;
		movingUp = false;
		movingDown = false;
	}
	
	HandleShooting(inputManager, deltaTime);
}

void Spaceship::Update(float deltaTime) 
{
	UpdateAnimation(deltaTime);

	for (auto it = missiles.begin(); it != missiles.end();) {
		it->Update(deltaTime);
		if (it->IsOffScreen()) {
			it = missiles.erase(it);
		}
		else {
			++it;
		}
	}

	//collisions check
}

void Spaceship::UpdateAnimation(float deltaTime)
{
	if (!movingLeft && !movingRight) {
		currentFrame = 3;
		frameTime = 0.0f;
		spriteRectPlayer.x = currentFrame * frameWidth;
		return;
	}

	frameTime += deltaTime;
	if (frameTime >= 0.1f) {
		frameTime = 0.0f;

		if (movingLeft) {
			currentFrame--;
			if (currentFrame < 0) {
				currentFrame = 0;
			}
		}
		else if (movingRight) {
			currentFrame++;
			if (currentFrame > 6) {
				currentFrame = 6;
			}
		}
	}
	spriteRectPlayer.x = currentFrame * frameWidth;
}

void Spaceship::HandleShooting(InputManager* inputManager, float deltaTime) {
	missileTimer -= deltaTime;

	bool shootKey = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_SPACE];
	bool shootButton = inputManager->IsButtonPressed(SDL_CONTROLLER_BUTTON_A);

	if ((shootKey || shootButton) && missileTimer <= 0.0f) {
	
		Missile missile(missileTexture, { (position.x + position.w / 2) - 8, (position.y - 16), 16, 16});
		
		missiles.push_back(missile);
		missile.CreateRigidBody(physics);
		missileTimer = missileCooldown;
	}
}

void Spaceship::Render(Renderer* renderer) 
{
	renderer->Render(texture, &spriteRectPlayer, &position);
	for (auto& missile : missiles) {
		missile.Render(renderer);
	}
	
	physics->Debug(&rigidbodyTransform, rigidbodyId);
}

void Spaceship::CreateRigidBody(Physics* physics)
{
	rigidbodyId = physics->CreateDynamicBody(posX, posY, true, 30, 20);
	rigidbodyTransform = physics->GetRigidBodyTransform(rigidbodyId);
	this->physics = physics;
	physics->Debug(&rigidbodyTransform, rigidbodyId);
}




Spaceship::~Spaceship() {

};
