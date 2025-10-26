#include "Platform/Window.hpp"
#include <iostream>

namespace Mira 
{
    class Application
    {
        private:

            bool Init(Mira::Backend::WindowSpecification&);

            
        public:
            Application(Mira::Backend::WindowSpecification&);
        
            void Run();

            
        private:

        
        std::unique_ptr<Mira::Backend::Window> m_window;

        bool m_running = true;
    };
}