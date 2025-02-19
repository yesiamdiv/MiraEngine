#include <iostream>
#include <Backend/MEWindow.h>
namespace Backend
{
    bool Window::Init(const std::string &title, int width, int height)
    {
 
        _sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
        if (!_sdlWindow)
        {
            std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
            return false;
        }

        //_glContext = SDL_GL_CreateContext(_sdlWindow);
        //if (!_glContext)
        //{
        //    std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        //    return false;
        //}
        

        //SDL_GL_SetSwapInterval(1); // Enable VSync
        return true;
    }

    void Window::Shutdown()
    {
        //SDL_GL_DeleteContext(_glContext);
        SDL_DestroyWindow(_sdlWindow);
        SDL_Quit();
    }

    SDL_Window* Window::GetSDLWindow()
    {
        return _sdlWindow;
    }



} // namespace Backend
