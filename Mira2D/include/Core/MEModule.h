#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

namespace Mira
{
    class Module
    {
    public:
        virtual void Update() = 0;
    private:
    };
} // namespace Mira
