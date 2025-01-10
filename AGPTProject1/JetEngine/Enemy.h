// #ifndef ENEMY_H
// #define ENEMY_H
// 
// #include "GameObject.h"
// #include "Renderer.h"
// #include "SDL.h"
// 
// class Enemy : public GameObject {
// public:
//     Enemy();
//     ~Enemy();
// 
//     void Initialize(SDL_Texture* texture, SDL_Rect startPosition, float speed, int frameWidth, int frameHeigth);
//     void Update(float deltaTime, int textureWidth, int textureHeight, int frameWidth, int frameHeigth) override;
//     void Render() override;
//     void SetEnemy(bool isLoner, bool isRusher);
// 
//     SDL_Rect GetBoundingBox() const;
// 
// private:
//     SDL_Renderer* renderer;
//     SDL_Texture* texture;
//     SDL_Rect position;
//     SDL_Rect frameRect; //the frame the sprite is at
//     int frameTime;
//     float speed;
//     bool isLoner;
//     bool isRusher;
// };
// 
// #endif
