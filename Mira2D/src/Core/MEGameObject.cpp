#include <utility>
#include <Core/MEGameObject.h>

namespace Mira
{
    void GameObject::AddModule(std::string indentifier, Module *module)
    {
        _modules[indentifier] = module;
    }

    template <typename T>
    T *GameObject::GetModule(std::string identifier)
    {
        auto it = _modules.find(identifier);
        if (it != _modules.end())
        {
            return dynamic_cast<T *>(it->second);
        }
        return nullptr;
    }

    void GameObject::UpdateModules(float deltatime)
    {
    }
}