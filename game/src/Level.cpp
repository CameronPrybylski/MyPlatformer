#include <Game/Level.h>
#include <Game/Player.h>
#include <Game/Obstacle.h>
#include <Game/Floor.h>


Level::Level(float screenWidth, float screenHeight, std::string filepath) : Scene(screenWidth, screenHeight), filepath(filepath)
{
    Init();
}

Level::~Level()
{

}

void Level::Init()
{
    LoadLevel(filepath);
}

void Level::LoadLevel(std::string filepath)
{

    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open level file.");
    }

    nlohmann::json j;
    file >> j;

    objectList.clear();
    objectMap.clear();
    for (const auto& obst : j["obstacles"]) {
        std::shared_ptr<GameObject> go;
        std::string name = obst.value("name", "Unnamed");
        glm::vec3 position = { obst["position"][0], obst["position"][1], obst["position"][2]};
        glm::vec3 scale = { obst["scale"][0], obst["scale"][1], obst["scale"][2]};
        glm::vec3 velocity = { obst["velocity"][0], obst["velocity"][1], obst["velocity"][2]};
        glm::vec4 color = { obst["color"][0], obst["color"][1], obst["color"][2], obst["color"][3]};
        bool isStatic = obst.value("isStatic", false);
        go = std::make_shared<Obstacle>(position, scale, velocity, color, "", isStatic);
        AddObject(obst.value("name", "Unnamed"), go);
    }
    player = nullptr;
    player = std::make_shared<Player>();
    std::shared_ptr<GameObject> floor = std::make_shared<Floor>();
    AddObject("player", player);
    AddObject("floor", floor);
    
    
    camera.Create(0.0f, screenWidth, 0.0f, screenHeight, -1.0f, 1.0f);
    
    leftScreenEdge = 0.0f;
    rightScreenEdge = screenWidth;

    gameOver = false;

}

void Level::LoadPhysics(PhysicsSystem& physics)
{
    glm::vec3 gravity;
    gravity.x = 0.0f;
    gravity.z = 0.0f;
    gravity.y = -1500.0f;
    physics.SetGravity(gravity);
    for(auto& obj : objectList)
    {
        physics.RegisterBody(obj->transform, obj->rigidBody);
    }
}

void Level::OnEvent(const Input &input)
{
    for(auto& obj : objectList)
    {
        obj->OnEvent(input);
    }
}

void Level::OnUpdate(const Input& input, PhysicsSystem &physics, float dt)
{
    //UpdatePhysics(physics, dt);
    physics.Update(dt);

    UpdateDynamicObjects(physics, dt);

    UpdateCamera();

    for(auto& obj : objectList)
    {
        obj->Update(input, dt);
    }

    if(player->alive == false)
    {
        gameOver = true;
    }
    if(gameOver)
    {
        EndScene("gameOver");
    }
}

void Level::UpdateDynamicObjects(PhysicsSystem& physics, float dt)
{
    for(auto& dynObj : objectMap)
    {
        if(!dynObj.second->rigidBody.isStatic && dynObj.second != player)
        {
            if(physics.CheckCollision(player->transform, dynObj.second->transform))
            {
                player->Hit(dt);
            }
        }
    }
}

void Level::UpdateCamera()
{
    float playerPositionChangeX = player->transform.position.x - player->rigidBody.previousPosition.x;
    if(  player->transform.position.x >= rightScreenEdge - (camera.GetProjMaxX() / 3) ||
        (player->transform.position.x <= leftScreenEdge  + (camera.GetProjMaxX() / 3) && 
         player->rigidBody.previousPosition.x - player->transform.position.x > 0      && 
         leftScreenEdge > 0.0f
        ))
    {
        glm::vec3 playerPostionChange(playerPositionChangeX, 0.0f, 0.0f);
        camera.OnUpdate(playerPostionChange);
        
        rightScreenEdge += playerPositionChangeX;
        leftScreenEdge += playerPositionChangeX;
    }
}