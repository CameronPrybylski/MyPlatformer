#include <Engine/Engine.h>
#include <Engine/Scene/Application.h>
#include <Game/Level.h>
#include <Game/GameOver.h>
#include <Game/Player.h>
#include <Game/Obstacle.h>
#include <iostream>

int main()
{
    
    Application app;
    
    if(!app.Create("Game", 1067, 800)){
        std::cout << "Error Creating Engine" << std::endl;
    }
    else{
    
        auto quadMesh = std::make_shared<QuadMesh>();
        AssetManager::LoadMesh("quadMesh", quadMesh);
        
        std::shared_ptr<Scene> level = std::make_shared<Level>(app.GetScreenWidth(), app.GetScreenHeight());
        std::shared_ptr<Scene> gameOver = std::make_shared<GameOver>();

        app.AddScene("basicScene", level);
        app.AddScene("gameOver", gameOver);
        app.SetScene("basicScene");
        
        AssetManager::LoadShader("objectShader", "/Users/cameronprzybylski/Documents/C++/C++ Projects/MyPlatformer/shaders/basic.vert", "/Users/cameronprzybylski/Documents/C++/C++ Projects/MyPlatformer/shaders/basic.frag");
        AssetManager::LoadShader("textureShader", "/Users/cameronprzybylski/Documents/C++/C++ Projects/MyPlatformer/shaders/texture.vert", "/Users/cameronprzybylski/Documents/C++/C++ Projects/MyPlatformer/shaders/texture.frag");
        app.Run();
    }
    return 0;
}