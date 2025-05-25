#pragma once

#include <glm.hpp>
//#include <glm/glm.hpp> // For transform matrices and vectors
#include <memory>
#include <cstdint>


namespace Mira
{
    namespace Graphics
    {
        // Forward declarations
        class METexture;
        class MEShader;
        
        // Enum for render layer (optional, for sorting)
        enum class MERenderLayer : uint8_t {
            Background = 0,
            Default = 1,
            Foreground = 2,
            UI = 3
        };
        
        // The RenderCommand encapsulates all data needed for a single draw call
        class MERenderCommand {
        public:
            // Pointer to texture to use (can be nullptr for shapes)
            std::shared_ptr<METexture> texture;
        
            // Pointer to shader to use
            std::shared_ptr<MEShader> shader;
        
            // Transform matrix (model matrix)
            glm::mat4 transform;
        
            // Color tint (RGBA)
            glm::vec4 color;
        
            // Layer for sorting
            MERenderLayer layer;
        
            // Optional: Z-order for fine sorting within a layer
            float zOrder = 0.0f;
        
            // Optional: User data or draw type (e.g., quad, circle, custom mesh)
            enum class Type { Quad, Circle, Custom } type = Type::Quad;
        
            // Any additional data for custom rendering (e.g., mesh pointer)
            void* userData = nullptr;
        
            MERenderCommand(
                std::shared_ptr<METexture> tex,
                std::shared_ptr<MEShader> shd,
                const glm::mat4& trans,
                const glm::vec4& col = glm::vec4(1.0f),
                MERenderLayer lyr = MERenderLayer::Default,
                float z = 0.0f,
                Type t = Type::Quad,
                void* data = nullptr
            )
                : texture(tex), shader(shd), transform(trans), color(col),
                  layer(lyr), zOrder(z), type(t), userData(data)
            {}
        
            // Comparison operator for sorting (by layer, then zOrder)
            bool operator<(const MERenderCommand& other) const {
                if (layer != other.layer)
                    return layer < other.layer;
                return zOrder < other.zOrder;
            }
        };
        
    }
}