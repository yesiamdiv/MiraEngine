#pragma once

#include <SDL.h>
#include <glad/glad.h>

namespace Mira
{
    class Texture
    {
        GLuint textureID;
        SDL_Texture *sdlTexture;

    public:
        void Bind();
    };
}
