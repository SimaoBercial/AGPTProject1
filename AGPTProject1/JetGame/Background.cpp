#include "Background.h"

Background::Background() {}

Background::~Background() {}

void Background::Initialize(const std::vector<SDL_Texture*>& textures, const std::vector<float>& scrollSpeeds, int width, int height) {
    for (size_t i = 0; i < textures.size(); ++i) {
        layers.push_back(BackgroundLayer(textures[i], width, height, scrollSpeeds[i]));
    }
}

void Background::Update(float deltaTime) {
    for (auto& layer : layers) {
        layer.Update(deltaTime);
    }
}

void Background::Render(Renderer* renderer) {
    for (auto& layer : layers) {
        layer.Render(renderer);
    }
}
