#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include <Core/MEModule.h>

namespace Mira
{
    class GameObject
    {
    public:
        GameObject();
    
        ~GameObject();
    
        virtual void Init();

        

        void AddModule(std::string indentifier ,Module *module);

        template <typename T>
        T *GetModule(std::string indentifier);

        void UpdateModules(float deltatime);
    private:
        std::unordered_map<std::string, Module *> _modules;
    };
} // namespace Mira
