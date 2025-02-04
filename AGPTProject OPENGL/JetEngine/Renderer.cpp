#include "Renderer.h"
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL.h>
#include "Shader.h"

Renderer::Renderer() : vao(0), vbo(0), shader(nullptr), window(0) {}

Renderer::~Renderer() {
    Shutdown();
}

bool Renderer::Initialize(SDL_Window* window) {
    shader = new Shader();
    if (!shader->LoadShader("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl")) {
        std::cerr << "Shader initialization failed!" << std::endl;
        delete shader;
        shader = nullptr;
        return false;
    }
    shader->Use();

    glm::mat4 projection = glm::ortho(0.0f, 640.0f, 480.0f, 0.0f, -1.0f, 1.0f);
    shader->SetMatrix4fv("projection", &projection[0][0]);

    glm::mat4 view = glm::mat4(1.0f);
    shader->SetMatrix4fv("view", &view[0][0]);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    float vertices[] = {
        0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,  1.0f, 0.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return true;
}


void Renderer::Shutdown() {
    if (shader) {
        delete shader;
        shader = nullptr;
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}



GLuint Renderer::LoadTexture(const std::string& filePath) {
    SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
    if (!surface) {
        std::cerr << "Failed to load texture: " << filePath << " | Error: " << SDL_GetError() << std::endl;
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    if (textureID == 0) {
        std::cerr << "Texture creation failed!" << std::endl;
        return 0;
    }
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_BGR, GL_UNSIGNED_BYTE, surface->pixels);
   
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "OpenGL error during glTexImage2D: " << err << std::endl;
    }

    glGenerateMipmap(GL_TEXTURE_2D);
    SDL_FreeSurface(surface);
    return textureID;
}


void Renderer::Clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Render(GLuint texture, const SDL_Rect& srcRect, const SDL_Rect& dstRect) {
    SDL_GL_MakeCurrent(window, SDL_GL_GetCurrentContext());

    shader->Use();

    GLint texLocation = shader->GetUniformLocation("ourTexture");
    if (texLocation != -1) {
        glUniform1i(texLocation, 0);
    }
    else {
        std::cerr << "Warning: Texture uniform 'ourTexture' not found in shader!" << std::endl;
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    GLint textureWidth, textureHeight;
    glBindTexture(GL_TEXTURE_2D, texture);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureWidth);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureHeight);

    float texLeft = static_cast<float>(srcRect.x) / static_cast<float>(textureWidth);
    float texRight = static_cast<float>(srcRect.x + srcRect.w) / static_cast<float>(textureWidth);
    float texTop = static_cast<float>(srcRect.y) / static_cast<float>(textureHeight);
    float texBottom = static_cast<float>(srcRect.y + srcRect.h) / static_cast<float>(textureHeight);

    float vertices[] = {
        0.0f, 1.0f, 0.0f, texLeft, texTop,
        1.0f, 0.0f, 0.0f, texRight, texBottom,
        0.0f, 0.0f, 0.0f, texLeft, texBottom,

        0.0f, 1.0f, 0.0f, texLeft, texTop,
        1.0f, 1.0f, 0.0f, texRight, texTop,
        1.0f, 0.0f, 0.0f, texRight, texBottom
    };

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(dstRect.x, dstRect.y, 0.0f));
    model = glm::scale(model, glm::vec3(dstRect.w, dstRect.h, 1.0f));
    shader->SetMatrix4fv("model", &model[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }
}




void Renderer::Present(SDL_Window* window) {
    SDL_GL_SwapWindow(window);
}
