#pragma once

#include <string>

#include <SDL.h>
#include <glad/glad.h>
#include <glm.hpp>
namespace Backend
{

    class Window
    {

    public:
        bool Init(const std::string &title, int width, int height);
        void Shutdown();

        int GetWidth() const { return _windowSize.y; };
        int GetHeight() const { return _windowSize.x; };
        glm::vec2 GetWindowSize() const { return _windowSize; };
        SDL_Window* GetSDLWindow();
    protected:
        //SDL_GLContext GetGLContext() const { return _glContext; }

        SDL_Window *_sdlWindow;
        //SDL_GLContext _glContext;

        glm::vec2 _windowSize;
        const std::string _title;
    };

} // namespace Mira
