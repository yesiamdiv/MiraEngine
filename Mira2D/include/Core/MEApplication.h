#pragma once

#include<Core/MEMaster.h>

namespace Mira
{
    class Application
    {
        public:
            Application();
            virtual void ApplicationOnBegin();
            virtual void ApplicationOnLooseFocus();
            virtual void ApplicationOnGainFocus();
        private:
    };
}