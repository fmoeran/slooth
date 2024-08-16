//
// Created by Felix Moeran on 16/08/2024.
//

#pragma once

#include <string>

namespace slt
{
    class Texture {
    public:
        Texture();
        Texture(std::string fileName);

        void load(std::string fileName);

        void use();

    private:
        unsigned int _ID;
        int _width, _height, _nrChannels;

    };
}
