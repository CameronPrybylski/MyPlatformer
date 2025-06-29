#include <Engine/Engine.h>
#include <iostream>

int main()
{
    Engine engine;
    if(!engine.Create("Game", 800, 800)){
        std::cout << "Error Creating Engine" << std::endl;
    }
    else{
        engine.Run();
    }
    return 0;
}