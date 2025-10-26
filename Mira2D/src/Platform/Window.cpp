#include "Platform/Window.hpp"
#include <iostream>
// #include "glad/glad.h"

namespace Mira
{
    namespace Backend
    {

        namespace details
        {
            void SDLWindowDeleter::operator()(SDL_Window* window){
                if(window) SDL_DestroyWindow(window);
            }
        
            void SDLGLContextDeleter::operator()(SDL_GLContext context){
                if(context) SDL_GL_DeleteContext(context);
            }
        }

        Window::Window(const WindowSpecification& specs)
        {
            this->m_specs = specs;
            this->Init();

        }

        bool Window::Init()
        {
            auto specs = this->m_specs;
         
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, specs.GLMajorVersion);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, specs.GLMinorVersion);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

            this->m_window.reset(SDL_CreateWindow(specs.Title.c_str(), specs.X, specs.Y, specs.Width, specs.Height, SDL_WINDOW_OPENGL) );
            
            if(!m_window.get()){
                throw std::runtime_error("Failed to create SDL Window: " + std::string(SDL_GetError()));
            }

            this->m_glContext.reset(SDL_GL_CreateContext(this->m_window.get()));

            if(!this->m_glContext.get()){
                throw std::runtime_error("Failed to create SDL GL Contexts: " + std::string(SDL_GetError()));
            }

            if (SDL_GL_SetSwapInterval(specs.VSync ? 1 : 0) < 0) {
                printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
            }
            
            return true;
        }

        void Window::SwapBuffer()
        {
            SDL_GL_SwapWindow(this->m_window.get());
        }
       
    }
}