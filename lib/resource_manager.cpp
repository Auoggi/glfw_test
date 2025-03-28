#include "resource_manager.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <stdio.h>
#include <sstream>
#include <fstream>

// Instantiate static variables
std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const char *vShaderFile, const char *fShaderFile, std::string name) {
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name) {
    return Shaders[name];
}

Shader ResourceManager::SetShader(const char *vShaderCode, const char *fShaderCode, std::string name) {
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode);
    Shaders[name] = shader;

    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const char *file, bool alpha, std::string name) {
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name) {
    return Textures[name];
}

void ResourceManager::Clear() {
    // (properly) delete all shaders	
    for(auto iter : Shaders) glDeleteProgram(iter.second.ID);
    // (properly) delete all textures
    for(auto iter : Textures) glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile) {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    try {
        // open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch(std::exception e) {
        fprintf(stdout, "ERROR::SHADER: Failed to read shader files\n");
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    // 2. now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char *file, bool alpha) {
    // create texture object
    Texture2D texture;
    if(alpha) {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    // now generate texture
    texture.Generate(width, height, data);
    // and finally free image data
    stbi_image_free(data);
    return texture;
}