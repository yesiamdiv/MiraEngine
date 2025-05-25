#pragma once

#include <glad/glad.h>
#include <memory>

namespace Mira
{    
    namespace Graphics
    {       
        // A simple OpenGL render target (framebuffer)
        class MERenderTarget {
        public:
            MERenderTarget(int width, int height);
            ~MERenderTarget();
        
            // Bind this render target (framebuffer) for rendering
            void bind();
        
            // Unbind (bind default framebuffer)
            void unbind();
        
            // Get the color texture (for post-processing, etc.)
            GLuint getColorTexture() const { return colorTexture; }
        
            // Get the framebuffer size
            int getWidth() const { return width; }
            int getHeight() const { return height; }
        
        private:
            GLuint framebuffer = 0;
            GLuint colorTexture = 0;
            GLuint depthStencilBuffer = 0;
            int width = 0;
            int height = 0;
        
            void createFramebuffer();
            void destroyFramebuffer();
        };
    }
}