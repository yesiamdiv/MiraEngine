
#include<Core/MEMaster.h>

namespace Mira
{
    Master* Master::_instance = nullptr;

    Master::Master()
        : _window(nullptr), _viewportX(0), _viewportY(0), _viewportW(0), _viewportH(0)
    {
        //Init();
    }

    Master::~Master()
    {
    }

    void Master::Setup()
    {
        std::cout << "Setup is complete." << std::endl;
    }

    void Master::Init()
    {

        if (!InitSDL())
        {
            exit(EXIT_FAILURE);
        }

        if (!InitOpenGL())
        {
            exit(EXIT_FAILURE);
        }

        std::cout << "Initialization is complete." << std::endl;
    }

    void Master::CreateWindow(const std::string &title, int w, int h)
    {
        InitSDL();
        _window = new Window();
        _window->Init(title, w, h);
        std::cout << "Window \"" << title << "\" created with dimensions " << w << "x" << h << "." << std::endl;
        InitOpenGL();
    }

    Master *Master::GetInstance()
    {
        if (!_instance)
        {
            _instance = new Master();
        }
        return _instance;
    }

    bool Master::InitSDL()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cout << "SDL2 could not initialize video subsystem" << std::endl;
            return false;
        }
    }

    bool Master::InitOpenGL()
    {

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        
        _glContext = SDL_GL_CreateContext(_window->GetSDLWindow());
        if (!_glContext)
        {
            std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
            return false;
        }
        SDL_GL_SetSwapInterval(1); // Enable VSync


        if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
            std::cout << "glad was not instialised" << std::endl;
            exit(1);
        }
        glDisable(GL_DEPTH_TEST);
        return true;
    }

    void Master::Run()
    {
        if(_isRunningState == false)
        {
            _isRunningState = true;
            MainLoop();
        }
    }

    void Master::MainLoop()
    {
        while (_isRunningState)
        {
            SDL_Event e;
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    std::cout << "Goodbye!" << std::endl;
                    _isRunningState = false;
                }
            }
        }
    }
}
