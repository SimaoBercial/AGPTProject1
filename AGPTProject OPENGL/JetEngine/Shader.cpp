#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

Shader::Shader() : programID(0) {}

Shader::~Shader() {
    if (programID) {
        glDeleteProgram(programID);
    }

}

bool Shader::LoadShader(const std::string& vertexPath, const std::string& fragmentPath) {

    std::string vertexSource = LoadShaderSource(vertexPath);
    std::string fragmentSource = LoadShaderSource(fragmentPath);

    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

    return LinkProgram(vertexShader, fragmentShader);
}

std::string Shader::LoadShaderSource(const std::string& filePath) {
    std::ifstream shaderFile(filePath);
    std::stringstream shaderStream;

    if (!shaderFile.is_open()) {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return "";
    }

    shaderStream << shaderFile.rdbuf();
    return shaderStream.str();
}

GLuint Shader::CompileShader(GLenum shaderType, const std::string& source) {
    GLuint shader = glCreateShader(shaderType);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            std::vector<char> infoLog(logLength);
            glGetShaderInfoLog(shader, logLength, nullptr, infoLog.data());
            std::cerr << "Shader compilation failed:\n" << infoLog.data() << std::endl;
        }
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

bool Shader::LinkProgram(GLuint vertexShader, GLuint fragmentShader) {
    programID = glCreateProgram();
    std::cout << "Created program with ID: " << programID << std::endl; 

    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        GLint logLength;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            std::vector<char> infoLog(logLength);
            glGetProgramInfoLog(programID, logLength, nullptr, infoLog.data());
            std::cerr << "Shader program linking failed:\n" << infoLog.data() << std::endl;
        }
        glDeleteProgram(programID);
        return false;
    }

    std::cout << "Shader program linked successfully with ID: " << programID << std::endl;

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}


void Shader::Use() {
    glUseProgram(programID);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "OpenGL Error after glUseProgram: " << err << std::endl;
    }
}


GLint Shader::GetUniformLocation(const std::string& name) {
    return glGetUniformLocation(programID, name.c_str());
}

void Shader::SetMatrix4fv(const std::string& name, const GLfloat* value) {
    GLint location = GetUniformLocation(name);
    if (location != -1) {
        glUniformMatrix4fv(location, 1, GL_TRUE, value);
    }
}

GLint Shader::GetProgramID() {
    return(programID);
}
