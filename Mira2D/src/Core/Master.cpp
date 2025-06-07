#include <iostream>
#include <Core/Master.h>
#include <glad/glad.h>

namespace Mira
{
    Master* Master::instance = nullptr;

    Master::Master():window(nullptr), running(false)
    {
        
    }

    Master::~Master()
    {
        delete window;
        window = nullptr;
    }

    Master* Master::GetInstance()
    {
        if(instance == nullptr)
        {
            instance = new Master();
        }

        return instance;
    };

    bool Master::Init(int width, int height, std::string title)
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            return false;
        }
        //initialise sdl image
        if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        {
            return false;
        }

        window = new Backend::Window();
        renderer = new Graphics::Renderer();
        if(!window->CreateWindow(width, height, title))
        {
            return false;
        }

        if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        {
            std::cout<<"Failed to initialize GLAD"<<std::endl;
            return false;
        }

        if(!renderer->Init(width, height, window))
        {
            return false;
        }

        return true;
    }


    // void Master::CloseWindow()
    // {
    //     window->CloseWindow();
    // }
    
    void Master::Run()
    {
        running = true;

        MainLoop();
    }

    void Master::MainLoop()
    {
        while(running)
        {
            SDL_Event event;

            SDL_PollEvent(&event);

            if(event.type == SDL_QUIT)
            {
                running = false;
                std::cout<<"Window closed"<<std::endl;
            }
        }
    }

}

