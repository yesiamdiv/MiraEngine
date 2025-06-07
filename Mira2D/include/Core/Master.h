#pragma once

#include <Backend/Window.h>
#include <Graphics/Renderer.h>
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>

namespace Mira
{
    class Master
    {
    public:

        static Master* GetInstance();

        bool Init(int width, int height, std::string title);

        void CloseWindow();

        bool IsRunning() {return running;}

        void Run();
        
        
        private:
        
        void MainLoop();
        
        // void Update();

        // void Render();
        
        
        private:
        
        Mira::Backend::Window* window;
        Mira::Graphics::Renderer* renderer;
        
        bool running;


        Master();
        ~Master();
        
        Master(const Master&) = delete;
        Master operator = (const Master&) = delete;

        static Master* instance;
    };
}

