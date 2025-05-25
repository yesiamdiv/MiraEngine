#include <Graphics/MERenderTarget.h>
#include <glad/glad.h>

namespace Mira
{
    
    namespace Graphics
    {   
        
        MERenderTarget::MERenderTarget(int w, int h)
            : width(w), height(h)
        {
            createFramebuffer();
        }
        
        MERenderTarget::~MERenderTarget() {
            destroyFramebuffer();
        }
        
        void MERenderTarget::createFramebuffer() {
            // Create framebuffer
            glGenFramebuffers(1, &framebuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        
            // Create color texture
            glGenTextures(1, &colorTexture);
            glBindTexture(GL_TEXTURE_2D, colorTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
        
            // Create depth-stencil buffer
            glGenRenderbuffers(1, &depthStencilBuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, depthStencilBuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthStencilBuffer);
        
            // Check framebuffer completeness
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
                // Handle error (log, assert, etc.)
            }
        
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
        
        void MERenderTarget::destroyFramebuffer() {
            if (depthStencilBuffer) {
                glDeleteRenderbuffers(1, &depthStencilBuffer);
                depthStencilBuffer = 0;
            }
            if (colorTexture) {
                glDeleteTextures(1, &colorTexture);
                colorTexture = 0;
            }
            if (framebuffer) {
                glDeleteFramebuffers(1, &framebuffer);
                framebuffer = 0;
            }
        }
        
        void MERenderTarget::bind() {
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
            glViewport(0, 0, width, height);
        }
        
        void MERenderTarget::unbind() {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            // You may want to reset the viewport to the window size here
        }
    } 
}