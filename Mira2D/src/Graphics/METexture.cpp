#include <Graphics/METexture.h>
#include <SDL_image.h>
#include <iostream>

namespace Mira
{
    
    namespace Graphics
    {
        
        
        METexture::METexture(const std::string& path) {
            loadFromFile(path);
        }
        
        METexture::~METexture() {
            glDeleteTextures(1, &textureID);
        }
        
        void METexture::bind(unsigned int slot) const {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, textureID);
        }
        
        void METexture::unbind() const {
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        
        void METexture::loadFromFile(const std::string& path) {
            SDL_Surface* surface = IMG_Load(path.c_str());
            if (!surface) {
                std::cerr << "Failed to load texture: " << path << " SDL_image error: " << IMG_GetError() << std::endl;
                return;
            }
        
            width = surface->w;
            height = surface->h;
            channels = surface->format->BytesPerPixel;
        
            GLenum format = GL_RGB;
            if (channels == 4) {
                format = GL_RGBA;
            }
        
            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_2D, textureID);
        
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, surface->pixels);
            glGenerateMipmap(GL_TEXTURE_2D);
        
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
            SDL_FreeSurface(surface);
        }
    } 
}