#pragma once

#include <string>
#include <SDL.h>

namespace Mira
{
    namespace Backend
    {
        class Master;
        class Window
        {
            public:
            friend class Master;
            
            Window();
            
            bool CreateWindow(int width, int height, std::string title);

            // void CloseWindow();

            // bool IsOpen();

            SDL_Window* GetSDLWindow(){return SDLWindow;};
            SDL_GLContext GetSDLContext(){return GLContext;};
            
            private:

            private:

            SDL_Window* SDLWindow;

            SDL_GLContext GLContext;

            bool isOpen;
        };

    }
}