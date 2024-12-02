#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SDL.h"

class GameObject {
public:
    virtual ~GameObject() = default;

    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual SDL_Rect GetBoundingBox() const = 0;

protected:
    SDL_Renderer* renderer = nullptr;
};

#endif
