#pragma once

#include <memory>
#include <vector>
#include <SDL.h>
#include <glm.hpp>
//#include <glm/glm.hpp>
#include <Graphics/MERenderCommand.h>
#include <Graphics/MERenderQueue.h>
#include <Graphics/MEShader.h>
#include <Graphics/METexture.h>
#include <Graphics/MERenderTarget.h>


namespace Mira
{
    namespace Graphics
    {
        
        
        // Forward declaration
        class MERenderTarget;
        
        class MERenderer {
        public:
            MERenderer();
            ~MERenderer();
        
            // Set the render target (e.g., screen or framebuffer)
            void setRenderTarget(std::shared_ptr<MERenderTarget> target);
        
            // Begin a new frame (clear screen, set up state)
            void beginFrame(const glm::vec4& clearColor = glm::vec4(0,0,0,1));
        
            // Submit a render command (alternative to using MERenderQueue directly)
            void submit(const MERenderCommand& command);
        
            // Render all commands in the queue
            void render(MERenderQueue& queue);
        
            // End the frame (present/swap buffers)
            void endFrame();
        
        private:
            std::shared_ptr<MERenderTarget> currentTarget;
            std::vector<MERenderCommand> immediateCommands; // For direct submission
        
            // Internal: actually draw a single command
            void drawCommand(const MERenderCommand& command);
        
            // Internal: sort and batch commands (optional, can be expanded)
            void sortCommands(std::vector<MERenderCommand>& commands);
        };
    }    
}
