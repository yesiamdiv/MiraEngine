#include <iostream>

#include <Backend/Window.h>

namespace Mira
{
    namespace Backend
    {
        Window::Window():SDLWindow(nullptr), GLContext(nullptr)
        {
        }
        
        bool Window::CreateWindow(int width, int height, std::string title)
        {
            SDLWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
        
            if(SDLWindow == nullptr)
            {
                std::cout<<"Window failed to create"<<std::endl;
                return false;
            }

            GLContext = SDL_GL_CreateContext(SDLWindow);

            if(GLContext == nullptr)
            {
                std::cout<<"GLContext failed to create"<<std::endl;
                return false;
            }

            return SDLWindow != nullptr;
        }
    }

}