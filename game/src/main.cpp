#include <Engine/Engine.h>
#include <Engine/Scene/Application.h>
#include <Game/Level.h>
#include <Game/Player.h>
#include <Game/Obstacle.h>
#include <iostream>

int main()
{
    //Engine engine;
    Application app;
    
    if(!app.Create("Game", 800, 800)){
        std::cout << "Error Creating Engine" << std::endl;
    }
    else{
    
        auto quadMesh = std::make_shared<QuadMesh>();
        AssetManager::LoadMesh("quadMesh", quadMesh);
        //std::shared_ptr<GameObject> player = std::make_shared<Player>();
        //std::shared_ptr<GameObject> obstacle = std::make_shared<Obstacle>();
        /*
        object->mesh = AssetManager::GetMesh("quadMesh");//quadMesh;
        object->shaderName = "objectShader";
        glm::vec3 position = {150.0f, 150.0f, 0.0f};
        object->transform.position = position;
        glm::vec3 scale{100.0f};
        object->transform.scale = scale;
        */
        //std::unique_ptr<Scene> basicScene = std::make_unique<Scene>();
        std::shared_ptr<Scene> level = std::make_shared<Level>();
        //level->AddObject("player", player);
        //level->AddObject("obstacle_1", obstacle);
        //level->SetOrthoProjMat(0.0f, 800.0f, 0.0f, 800.0f, -1.0f, 1.0f);
        app.GetEngine().GetSceneManager()->AddScene("basicScene", level);
        app.GetEngine().GetSceneManager()->SwitchTo("basicScene");
        //Scene& scene = *app.GetEngine().GetSceneManager()->GetCurrentScene();
        //scene.AddObject("player", player);
        //scene.AddObject("obstacle_1", obstacle);
        //scene.SetOrthoProjMat(0.0f, 800.0f, 0.0f, 800.0f, -1.0f, 1.0f);
        AssetManager::LoadShader("objectShader", "/Users/cameronprzybylski/Documents/C++/C++ Projects/MyPlatformer/shaders/basic.vert", "/Users/cameronprzybylski/Documents/C++/C++ Projects/MyPlatformer/shaders/basic.frag");
        app.Run();
    }
    return 0;
}