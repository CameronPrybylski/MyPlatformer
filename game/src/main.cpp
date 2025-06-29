#include <Engine/Engine.h>
#include <iostream>

int main()
{
    Engine engine;
    
    if(!engine.Create("Game", 800, 800)){
        std::cout << "Error Creating Engine" << std::endl;
    }
    else{
        Application app;
    
        auto quadMesh = std::make_shared<QuadMesh>();
        std::shared_ptr<GameObject> object = std::make_shared<GameObject>();
        object->mesh = quadMesh;
        object->shaderName = "objectShader";
        glm::vec3 position = {150.0f, 150.0f, 0.0f};
        object->transform.position = position;
        glm::vec3 scale{100.0f};
        object->transform.scale = scale;
        //std::unique_ptr<Scene> basicScene = std::make_unique<Scene>();
        app.GetSceneManager()->AddScene("basicScene", std::make_shared<Scene>());
        app.GetSceneManager()->SwitchTo("basicScene");
        Scene& scene = *app.GetSceneManager()->GetCurrentScene();
        scene.AddObject(object);
        scene.SetOrthoProjMat(0.0f, 800.0f, 0.0f, 800.0f, -1.0f, 1.0f);
        AssetManager::LoadShader("objectShader", "../shaders/basic.vert", "../shaders/basic.frag");
        engine.SetApp(app);
        engine.Run();
    }
    return 0;
}