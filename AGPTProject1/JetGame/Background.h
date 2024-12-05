#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "SDL.h"
#include "Renderer.h"
#include <vector>

class BackgroundLayer {
public:
	SDL_Texture* texture;
	SDL_Rect rect;
	float scrollSpeed;
	float offsetY;

	BackgroundLayer(SDL_Texture* tex, int width, int height, float speed)
		: texture(tex), scrollSpeed(speed), offsetY(0.0f) {
		rect = { 0, 0, width, height };
	}

	void Update(float deltaTime) {
		offsetY -= scrollSpeed * deltaTime;

		if (offsetY <= -rect.h) {
			offsetY = rect.h;
		}
	}

	void Render(Renderer* renderer) {
		SDL_Rect renderRect1 = { 0, static_cast<int>(-offsetY), rect.w, rect.h };
		SDL_Rect renderRect2 = { 0, static_cast<int>(offsetY), rect.w, rect.h };

		renderer->Render(texture, &renderRect1, &renderRect1);
		renderer->Render(texture, &renderRect2, &renderRect2);
	}
};

class Background {
public:
    Background();
    ~Background();

    void Initialize(const std::vector<SDL_Texture*>& textures, const std::vector<float>& scrollSpeeds, int width, int height);
    void Update(float deltaTime);
    void Render(Renderer* renderer);

private:
    std::vector<BackgroundLayer> layers;
};

#endif
