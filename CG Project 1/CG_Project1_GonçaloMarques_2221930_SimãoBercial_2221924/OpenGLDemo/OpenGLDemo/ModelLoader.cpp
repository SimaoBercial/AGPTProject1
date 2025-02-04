#include "ModelLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "stb_image.h"

ModelLoader::ModelLoader() : VAO(0), VBO(0), EBO(0) {}

ModelLoader::~ModelLoader() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

bool ModelLoader::loadModel(const std::string& objPath, Shader& shaderProgram) {
    std::ifstream file(objPath);
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << objPath << std::endl;
        return false;
    }

    std::string directory = objPath.substr(0, objPath.find_last_of('/'));
    std::string mtlPath;
    std::vector<glm::vec3> positions, normals;
    std::vector<glm::vec2> texCoords;
    std::string currentMaterial;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "mtllib") {
            ss >> mtlPath;
            mtlPath = directory + "/" + mtlPath;
        } else if (type == "usemtl") {
            ss >> currentMaterial;
        } else if (type == "v") {
            glm::vec3 position;
            ss >> position.x >> position.y >> position.z;
            positions.push_back(position);
        } else if (type == "vt") {
            glm::vec2 texCoord;
            ss >> texCoord.x >> texCoord.y;
            texCoords.push_back(texCoord);
        } else if (type == "vn") {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        } else if (type == "f") {
            GLuint vIdx[3], tIdx[3], nIdx[3];
            for (int i = 0; i < 3; ++i) {
                char delimiter;
                ss >> vIdx[i] >> delimiter >> tIdx[i] >> delimiter >> nIdx[i];
                Vertex vertex = {
                    positions[vIdx[i] - 1],
                    normals[nIdx[i] - 1],
                    texCoords[tIdx[i] - 1]
                };
                vertices.push_back(vertex);
                indices.push_back(static_cast<GLuint>(vertices.size() - 1));
            }
        }
    }

    file.close();

    if (!mtlPath.empty() && !loadMTL(mtlPath)) {
        std::cerr << "Failed to load MTL file: " << mtlPath << std::endl;
    }

    setupMesh(shaderProgram);
    return true;
}

bool ModelLoader::loadMTL(const std::string& mtlPath) {
    std::ifstream file(mtlPath);
    if (!file.is_open()) {
        std::cerr << "Failed to open MTL file: " << mtlPath << std::endl;
        return false;
    }

    Material material;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "newmtl") {
            if (!material.name.empty()) {
                materials[material.name] = material;
            }
            ss >> material.name;
            material.diffuseMap.id = 0;
            material.diffuseColor = glm::vec3(1.0f);
        } else if (type == "Kd") {
            ss >> material.diffuseColor.r >> material.diffuseColor.g >> material.diffuseColor.b;
        } else if (type == "map_Kd") {
            std::string texturePath;
            ss >> texturePath;
            texturePath = mtlPath.substr(0, mtlPath.find_last_of('/')) + "/" + texturePath;
            loadTexture(texturePath, material.diffuseMap);
        }
    }

    if (!material.name.empty()) {
        materials[material.name] = material;
    }

    file.close();
    return true;
}

bool ModelLoader::loadTexture(const std::string& path, Texture& texture) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    stbi_set_flip_vertically_on_load(true);
    int width, height, channels;
    unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (!image) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return false;
    }

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(image);

    texture.id = textureID;
    texture.type = "texture_diffuse";
    texture.path = path;

    return true;
}

void ModelLoader::setupMesh(Shader& shaderProgram) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    shaderProgram.setVertexAttribPointer("position", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); 
    shaderProgram.setVertexAttribPointer("normal", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal)); 
    shaderProgram.setVertexAttribPointer("texCoord", 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords)); 

    glBindVertexArray(0);
}

void ModelLoader::draw(Shader& shaderProgram) {
    shaderProgram.use();

    for (const auto& pair : materials) {
        const Material& material = pair.second; 

        if (material.diffuseMap.id != 0) { 
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, material.diffuseMap.id);
            shaderProgram.setInt("texture_diffuse", 0); 
        }
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);
}