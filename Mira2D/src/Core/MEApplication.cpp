#include <Core/MEApplication.h>

namespace Mira
{
    Application::Application()
    {
        auto master = Master::GetInstance();
        if(master)
        {
            //master->Init();
        }
        else
        {
            std::cout << "Could not create master" << std::endl;
            exit(EXIT_FAILURE);
        }
        
    }

    void Application::ApplicationOnBegin()
    {
    }

    void Application::ApplicationOnLooseFocus()
    {
    }

    void Application::ApplicationOnGainFocus()
    {
    }


}