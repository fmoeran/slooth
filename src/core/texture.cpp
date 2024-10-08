//
// Created by Felix Moeran on 16/08/2024.
//

#include "texture.hpp"
#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

namespace slt
{
    Texture::Texture() {
        glGenTextures(1, &_ID);
    }

    Texture::Texture(std::string fileName) {
        glGenTextures(1, &_ID);
        load(fileName);
    }

    void Texture::load(std::string fileName) {
        unsigned char *data = stbi_load(fileName.c_str(), &_width, &_height, &_nrChannels, 0);
        glBindTexture(GL_TEXTURE_2D, _ID);
        if (data) {
            GLenum format;
            if (_nrChannels == 4) format = GL_RGBA;
            else if (_nrChannels == 3) format = GL_RGB;
            glTexImage2D(GL_TEXTURE_2D, 0, format, _width, _height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture: " << fileName << std::endl;
        }
        stbi_image_free(data);
    }


    void Texture::use() {
        glBindTexture(GL_TEXTURE_2D, _ID);
    }
}
