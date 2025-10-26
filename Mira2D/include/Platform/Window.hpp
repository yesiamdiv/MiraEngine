#include <string>
#include <iostream>
#include "SDL2/SDL.h"

// struct SDL_Window;
// typedef void* SDL_GLContext;

namespace Mira 
{
    namespace Backend
    {
        typedef struct {
            std::string Title = "Mira2D Engine";
            int Width = 1280;
            int Height = 720;
            int X;
            int Y;
            int GLMajorVersion = 4;
            int GLMinorVersion = 1;
            bool VSync = true;
        } WindowSpecification;

        namespace details 
        {
            struct SDLWindowDeleter {
                void operator()(SDL_Window* window);
            };
        
            struct SDLGLContextDeleter {
                void operator()(SDL_GLContext context);
            };
        }

        class Window
        {
            private:
                bool Init();

            public:
                Window(const WindowSpecification& specs = WindowSpecification{});
                Window() = default; 

                Window(const Window&) = delete;
                Window& operator=(const Window&) = delete;

                void SwapBuffer();

            private:
                WindowSpecification m_specs;
                std::unique_ptr<SDL_Window, details::SDLWindowDeleter> m_window;
                std::unique_ptr<void, details::SDLGLContextDeleter> m_glContext;

        };
    }

}