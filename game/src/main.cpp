#include <Core/Master.h>
#include <iostream>

//GET_ASSET_PATH("//lol")

using namespace Mira;

int main(int argc, char* argv[])
{
    Master *master = Master::GetInstance();

    if(!master->Init(800, 600, "Mira"))
    {
        std::cout << "Failed to initialize master" << std::endl;
        return -1;
    }
    master->Run();

    return 0;
}