#ifndef DRONE_H
#define DRONE_H

#include "Enemies.h"
#include "Renderer.h"
#include <cmath>

class Drone : public Enemies {
public:
    Drone(GLuint texture, SDL_Rect position, int textureWidth, int textureHeight);
    ~Drone();

    void Update(float deltaTime) override;
    void Render(Renderer* renderer) override;
    SDL_Rect GetBoundingBox() const override;
    void CreateRigidBody(Physics* physics) override;

private:
    GLuint texture;
    float frameTime;
    int currentFrame;
    int numFrames;
    int textureWidth;
    int textureHeight;
    float moveSpeed;
};

#endif
