#pragma once
#include <iostream>
#include <string>

#include <Backend/MEWindow.h>
#include <Core/MEGameObject.h>
#include <Core/MEModule.h>
#include <Core/MEScene.h>
#include <Core/METransform.h>
#include <glad/glad.h>

using namespace Backend;

namespace Mira
{

    class Master
    {
        Master();
        ~Master();

        Master(const Master&) = delete;
        Master operator = (const Master&) = delete;

        static Master* _instance;

    public:
        void Setup();
       
        void Init();

        void CreateWindow(const std::string& title, int w, int h);

        static Master* GetInstance();

        void Run();
    protected:
        bool InitSDL();

        bool InitOpenGL();


        void MainLoop();

    protected:

        Backend::Window* _window;
        SDL_GLContext _glContext;
        
        int _viewportX;
        int _viewportY;
        int _viewportW;
        int _viewportH;

        bool _isRunningState = false;
    };
    
}