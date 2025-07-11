#include <Game/Level.h>
#include <Game/Player.h>
#include <Game/Obstacle.h>
#include <Game/Floor.h>


Level::Level()
{
    player = std::make_shared<Player>();
    //std::shared_ptr<GameObject> player1 = player;
    /*
    transform.position = {750.0f, 25.0f, 0.0f};
    transform.scale = {50.0f, 50.0f, 0.0f};
    rigidBody.velocity.x = -500.0f;
    rigidBody.isStatic = false;
    */
    std::shared_ptr<GameObject> obstacle = std::make_shared<Obstacle>(glm::vec3(750.0f, 25.0f, 0.0f), 
    glm::vec3(50.0f, 50.0f, 0.0f), glm::vec3(-250.0f, 0.0f, 0.0f), false);
    std::shared_ptr<GameObject> obstacle2 = std::make_shared<Obstacle>(glm::vec3(400.0f, 150.0f, 0.0f), 
    glm::vec3(400.0f, 50.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), true);
    std::shared_ptr<GameObject> floor = std::make_shared<Floor>();
    AddObject("player", player);
    AddObject("obstacle_1", obstacle);
    AddObject("obstacle_2", obstacle2);
    AddObject("floor", floor);
    SetOrthoProjMat(0.0f, 1067.0f, 0.0f, 800.0f, -1.0f, 1.0f);
    leftScreenEdge = 0.0f;
    rightScreenEdge = 1067.0f;
}

Level::Level(std::unordered_map<std::string, std::shared_ptr<GameObject>> objects)
{
    for(auto& obj : objects)
    {
        AddObject(obj.first, obj.second);
    }
    SetOrthoProjMat(0.0f, 800.0f, 0.0f, 800.0f, -1.0f, 1.0f);

}

Level::~Level()
{

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
    
    for(auto& obj : objectList)
    {   
        if(!obj->rigidBody.isStatic)
        {
            physics.Integrate(obj->transform, obj->rigidBody, dt);
        }
    }
    for(auto& obj : objectList)
    {
        if(!obj->rigidBody.isStatic)
        {
            for(auto& staticObj : objectList)
            {
                if(staticObj->rigidBody.isStatic)
                //if(staticObj != obj)
                {   
                    physics.ResolveCollision(obj->transform, obj->rigidBody, staticObj->transform, staticObj->rigidBody);
                }

            }            
        }
    }
    //std::shared_ptr<GameObject> player = objectMap["player"];
    if(player->alive == false)
    {
        gameOver = true;
    }

    UpdateCamera();

    for(auto& obj : objectList)
    {
        obj->Update(input, dt);
    }
}

void Level::UpdateCamera()
{
    if(player->transform.position.x >= rightScreenEdge - 300.0f)
    {
        camera.position.x = camera.position.x + std::abs(player->rigidBody.previousPosition.x - player->transform.position.x);
        rightScreenEdge += std::abs(player->rigidBody.previousPosition.x - player->transform.position.x);
        leftScreenEdge  += std::abs(player->rigidBody.previousPosition.x - player->transform.position.x);
    }
    if(player->transform.position.x <= leftScreenEdge + 300.0f)
    {
        camera.position.x = camera.position.x - std::abs(player->rigidBody.previousPosition.x - player->transform.position.x);
        rightScreenEdge -= std::abs(player->rigidBody.previousPosition.x - player->transform.position.x);
        leftScreenEdge  -= std::abs(player->rigidBody.previousPosition.x - player->transform.position.x);
    }
}