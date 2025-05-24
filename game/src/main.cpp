#include <iostream>
#include<Core/Mira2D.h>

using namespace Mira;

class MyGame: public Application
{
   public:
       MyGame() {};

       void Init()
       {
           auto master = Master::GetInstance();
           master->CreateWindow("MyGame", _windowW, _windowH);
           master->Run();
           
       }
   private:
       int _windowW = 640;
       int _windowH = 640;
};



int main(int argc, char* argv[])
// int main()
{
   MyGame game;
   game.Init();
   
   return 0;
}


// #include <iostream>
//
// int main()
// {
//     std::cout<<"Hellp world"<<std::endl;
//    return 0;
// }

