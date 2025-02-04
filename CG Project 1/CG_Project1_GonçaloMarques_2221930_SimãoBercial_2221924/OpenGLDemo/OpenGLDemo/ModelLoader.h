#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <string>
#include <vector>
#include <map>
#include <GLAD/glad.h>
#include <glm/glm.hpp>
#include "Shader.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Texture {
    GLuint id = 0;
    std::string type = "";
    std::string path = "";
};

struct Material {
    std::string name = "";
    Texture diffuseMap;
    glm::vec3 diffuseColor = glm::vec3(1.0f);
};

class ModelLoader {
public:
    ModelLoader();
    ~ModelLoader();

    bool loadModel(const std::string& objPath, Shader& shaderProgram);
    void draw(Shader& shaderProgram);

private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::map<std::string, Material> materials;

    GLuint VAO, VBO, EBO;

    bool loadMTL(const std::string& mtlPath);
    bool loadTexture(const std::string& path, Texture& texture);
    void setupMesh(Shader& shaderProgram);
};

#endif