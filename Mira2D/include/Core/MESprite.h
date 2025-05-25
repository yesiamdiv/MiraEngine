// Sprite.h
#pragma once
#include <Graphics/METexture.h>
#include <Graphics/MERenderCommand.h>
#include <memory>
#include <glm.hpp>
//#include <glm/glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace Mira {

    class Sprite {
    public:
        Sprite(const std::string& imagePath, const glm::vec2& pos)
            : position(pos)
        {
            texture = std::make_shared<Mira::Graphics::METexture>(imagePath);
        }
    
        void draw(Mira::Graphics::MERenderQueue& queue) {
            Mira::Graphics::MERenderCommand cmd(
                texture, // texture
                nullptr, // shader (use default if you have one)
                glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f)), // transform
                glm::vec4(1.0f) // color
            );
            queue.addCommand(cmd);
        }
    
    private:
        std::shared_ptr<Mira::Graphics::METexture> texture;
        glm::vec2 position;
    };
}