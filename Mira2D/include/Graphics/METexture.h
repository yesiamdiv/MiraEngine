#pragma once

#include <string>
#include <glad/glad.h>
#include <glm.hpp>
//#include <glm/glm.hpp>

namespace Mira
{
    
    namespace Graphics
    {
        class METexture {
        public:
            METexture(const std::string& path);
            ~METexture();
        
            void bind(unsigned int slot = 0) const;
            void unbind() const;
        
            int getWidth() const { return width; }
            int getHeight() const { return height; }
            GLuint getID() const { return textureID; }
        
        private:
            GLuint textureID = 0;
            int width = 0;
            int height = 0;
            int channels = 0;
        
            void loadFromFile(const std::string& path);
        };
    }
}
