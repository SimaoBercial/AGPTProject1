#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>

class Shader {
public:
    Shader();
    ~Shader();

    bool LoadShader(const std::string& vertexPath, const std::string& fragmentPath);
    void Use();
    GLint GetUniformLocation(const std::string& name);
    void SetMatrix4fv(const std::string& name, const GLfloat* value);
    GLint GetProgramID();

private:
    GLuint programID;

    std::string LoadShaderSource(const std::string& filePath);
    GLuint CompileShader(GLenum shaderType, const std::string& source);
    bool LinkProgram(GLuint vertexShader, GLuint fragmentShader);
};

#endif
