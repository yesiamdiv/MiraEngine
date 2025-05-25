
#include <iostream>
#include<Core/Mira2D.h>
#include <Graphics/METexture.h>
#include <Graphics/MERenderQueue.h>
#include <Graphics/MERenderer.h>
#include <glm.hpp>
//#include <glm/glm.hpp>
#include <Core/MESprite.h> // The Sprite class above

using namespace Mira;

class MyGame: public Application
{
   public:
       MyGame() {};

       void Init()
       {
           auto master = Master::GetInstance();
           master->CreateWindow("MyGame", _windowW, _windowH);
           //master->Run();
           
       }

       void Run() {
            auto master = Master::GetInstance();

           Mira::Graphics::MERenderer renderer;
           Mira::Graphics::MERenderQueue renderQueue;

           std::string imagePath = std::string(ASSET_PATH) + "my_image.png";
           Sprite sprite(imagePath, glm::vec2(100, 100)); // Path to your image

           bool running = true;
           SDL_Event e;
           while (running) {
               while (SDL_PollEvent(&e)) {
                   if (e.type == SDL_QUIT) running = false;
               }

               renderQueue.clear();
               sprite.draw(renderQueue);

               renderer.beginFrame();
               renderer.render(renderQueue);
               renderer.endFrame();

               // SDL_GL_SwapWindow(master->GetWindow()->GetSDLWindow()); // Removed due to inaccessibility

               // If the engine handles buffer swapping internally, you can safely remove this line.
               // Otherwise, expose a public method in Master to perform the swap, e.g.:
               // master->SwapBuffers();
           }
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
   game.Run();
   return 0;
}


// #include <iostream>
//
// int main()
// {
//     std::cout<<"Hellp world"<<std::endl;
//    return 0;
// }

