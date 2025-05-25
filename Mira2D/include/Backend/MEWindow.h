#pragma once

#include <string>
#include <SDL.h>
#include <glad/glad.h>
//#include <glm/glm.hpp>
#include <glm.hpp>

namespace Mira
{
    namespace Backend
    {
        class Window
        {
        public:
            Window(const std::string& title = "Mira Window", int width = 800, int height = 600)
                : _title(title), _windowSize(width, height), _sdlWindow(nullptr) {}

            bool Init(const std::string& title, int width, int height);

            void Shutdown();

            int GetWidth() const { return static_cast<int>(_windowSize.x); }
            int GetHeight() const { return static_cast<int>(_windowSize.y); }
            glm::vec2 GetWindowSize() const { return _windowSize; }

            SDL_Window* GetSDLWindow();

        protected:
            SDL_Window* _sdlWindow;
            glm::vec2 _windowSize;
            std::string _title;
        };
    }
}
