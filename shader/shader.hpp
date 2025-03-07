#ifndef SHADER_H
#define SHADER_H

#include <glad/gl.h>

#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>

// From https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader_s.h
void checkCompileErrors(GLuint shader, const char* type) {
    int success;
    char infoLog[1024];
    if(type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            fprintf(stdout, "ERROR::SHADER_COMPILATION_ERROR of type: %s\n%s\n -- --------------------------------------------------- -- \n", type, infoLog);
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            fprintf(stdout, "ERROR::PROGRAM_LINKING_ERROR of type: %s\n%s\n -- --------------------------------------------------- -- \n", type, infoLog);
        }
    }
}

GLuint createShaderProgram(const char* vertex_path, const char* fragment_path) {
    std::string vertexCode, fragmentCode; 
    try { 
        std::ifstream vShaderFile, fShaderFile; 
        vShaderFile.open(vertex_path); 
        fShaderFile.open(fragment_path); 
        std::stringstream vShaderStream, fShaderStream; 
        vShaderStream << vShaderFile.rdbuf(); 
        fShaderStream << fShaderFile.rdbuf(); 
        vShaderFile.close(); 
        fShaderFile.close(); 
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch(std::ifstream::failure& e) {
        fprintf(stdout, "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: %s\n", e.what());
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    const GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    const GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    const GLuint ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return ID;
}
#endif