#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <Graphics/MERenderCommand.h>

namespace Mira
{
    
    namespace Graphics
    {
        class MERenderQueue {
            public:
                // Add a render command to the queue
                void addCommand(const MERenderCommand& command) {
                    commands.push_back(command);
                }
        
                // Clear the queue
                void clear() {
                    commands.clear();
                }
        
                // Get all commands (for processing)
                const std::vector<MERenderCommand>& getCommands() const {
                    return commands;
                }
        
                // Sort commands by layer and z-order
                void sortCommands() {
                    std::sort(commands.begin(), commands.end());
                }
            private:
                std::vector<MERenderCommand> commands; // List of render commands
                // Note: You may want to implement a custom allocator for performance
                // or use a memory pool if this queue is used frequently.
                // For now, we use std::vector which is sufficient for most cases.
                // This can be extended with more complex sorting or batching logic
                // if needed in the future.
                // Additional optimizations could include grouping commands by texture
                // or shader to reduce state changes during rendering.
                // This class is designed to be simple and efficient for typical 2D rendering tasks.
        
        
                // Future enhancements could include:
                // - Support for batching similar commands to reduce draw calls
                // - Integration with a graphics API for actual rendering
                // - Custom memory management for performance
                // - Support for different render targets (e.g., offscreen rendering)
                // - More complex sorting strategies based on performance profiling
                // - Support for different render layers and priorities
                // - Integration with a scene graph or entity-component system for better organization
                // - Support for dynamic updates to the queue (e.g., adding/removing commands at runtime)
                // - Support for different render states (e.g., blending, depth testing)
                // - Support for different render targets (e.g., offscreen rendering)
                // - Support for different render layers and priorities
                // - Support for dynamic updates to the queue (e.g., adding/removing commands at runtime)
                
        };
    }
}
