#include <Graphics/MERenderer.h>
#include <Graphics/MERenderTarget.h>
#include <Graphics/METexture.h>
#include <Graphics/METexture.h>
#include <algorithm>
#include <glad/glad.h> // Or your OpenGL loader
#include <SDL.h>


namespace Mira
{
    
    namespace Graphics
    {
        
        // Constructor
        MERenderer::MERenderer() {
            // Initialization if needed
        }
        
        // Destructor
        MERenderer::~MERenderer() {
            // Cleanup if needed
        }
        
        void MERenderer::setRenderTarget(std::shared_ptr<MERenderTarget> target) {
            currentTarget = target;
            // Bind the framebuffer or set the render target as needed
            // (Implementation depends on your MERenderTarget)
        }
        
        void MERenderer::beginFrame(const glm::vec4& clearColor) {
            // Bind render target if any
            if (currentTarget) {
                currentTarget->bind();
            } else {
                glBindFramebuffer(GL_FRAMEBUFFER, 0); // Default framebuffer
            }
            glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            immediateCommands.clear();
        }
        
        void MERenderer::submit(const MERenderCommand& command) {
            immediateCommands.push_back(command);
        }
        
        void MERenderer::render(MERenderQueue& queue) {
            // Combine immediate commands and queue commands
            std::vector<MERenderCommand> allCommands = immediateCommands;
            const auto& queued = queue.getCommands();
            allCommands.insert(allCommands.end(), queued.begin(), queued.end());
        
            // Sort commands (by layer, zOrder, etc.)
            sortCommands(allCommands);
        
            // Draw all commands
            for (const auto& cmd : allCommands) {
                drawCommand(cmd);
            }
        }
        
        void MERenderer::endFrame() {
            // Unbind render target if needed
            if (currentTarget) {
                currentTarget->unbind();
            }
            // If using SDL, swap the window buffers here (handled elsewhere in your app)
            // SDL_GL_SwapWindow(window);
        }
        
        void MERenderer::drawCommand(const MERenderCommand& command) {
            // Bind shader
            if (command.shader) {
                command.shader->bind();
                // Set uniforms (transform, color, etc.)
                command.shader->setMat4("u_Model", command.transform);
                command.shader->setVec4("u_Color", command.color);
                // ...set other uniforms as needed
            }
        
            // Bind texture
            if (command.texture) {
                command.texture->bind(0); // Bind to texture unit 0
                if (command.shader) {
                    command.shader->setInt("u_Texture", 0);
                }
            }
        
            // Draw geometry based on command type
            switch (command.type) {
                case MERenderCommand::Type::Quad:
                    // Draw a quad (you need to have a VAO/VBO for a quad)
                    // Example: glBindVertexArray(quadVAO); glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
                    break;
                case MERenderCommand::Type::Circle:
                    // Draw a circle (if supported)
                    break;
                case MERenderCommand::Type::Custom:
                    // Use userData for custom draw
                    break;
            }
        
            // Unbind as needed (optional)
            if (command.texture) {
                command.texture->unbind();
            }
            if (command.shader) {
                command.shader->unbind();
            }
        }
        
        void MERenderer::sortCommands(std::vector<MERenderCommand>& commands) {
            std::sort(commands.begin(), commands.end());
        }
    }
}