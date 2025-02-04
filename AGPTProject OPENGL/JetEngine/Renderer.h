#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <glm/glm.hpp>
#include <string>
#include <glad/glad.h>

class Shader;

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool Initialize(SDL_Window* window);
    void Shutdown();
    GLuint LoadTexture(const std::string& filePath);
    void Clear();
    void Render(GLuint texture, const SDL_Rect& srcRect, const SDL_Rect& dstRect);
    void Present(SDL_Window* window);

private:
    GLuint vao;
    GLuint vbo;
    Shader* shader;
    SDL_Window* window;
};

#endif // RENDERER_H
