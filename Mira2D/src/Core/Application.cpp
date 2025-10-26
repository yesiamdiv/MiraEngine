#include "Core/Application.hpp"
#include "glad/glad.h"
namespace Mira
{
    Mira::Application::Application(Mira::Backend::WindowSpecification& specs)
    {
        if(!this->Init(specs))
        {

        }
    }

    bool Mira::Application::Init(Mira::Backend::WindowSpecification& specs)
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        
        this->m_window = std::make_unique<Mira::Backend::Window>(specs);

        if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        {
            return false;
        }
    }
    
    void Mira::Application::Run()
    {

        while(this->m_running)
        {
        }
        
    }


}