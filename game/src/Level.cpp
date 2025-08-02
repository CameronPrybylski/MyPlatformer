#include <Game/Level.h>
#include <Game/Player.h>
#include <Game/Obstacle.h>
#include <Game/Floor.h>


Level::Level(float screenWidth, float screenHeight)
{
    player = std::make_shared<Player>();
    
    std::shared_ptr<GameObject> obstacle = std::make_shared<Obstacle>(glm::vec3(750.0f, 25.0f, 0.0f), 
    glm::vec3(50.0f, 50.0f, 0.0f), glm::vec3(-250.0f, 0.0f, 0.0f), false);
    
    std::shared_ptr<GameObject> obstacle2 = std::make_shared<Obstacle>(glm::vec3(400.0f, 150.0f, 0.0f), 
    glm::vec3(400.0f, 50.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), true);
    
    std::shared_ptr<GameObject> floor = std::make_shared<Floor>();
    
    AddObject("player", player);
    AddObject("obstacle_1", obstacle);
    AddObject("obstacle_2", obstacle2);
    AddObject("floor", floor);
    
    camera.Create(0.0f, screenWidth, 0.0f, screenHeight, -1.0f, 1.0f);
    
    leftScreenEdge = 0.0f;
    rightScreenEdge = screenWidth;
}

Level::Level(std::unordered_map<std::string, std::shared_ptr<GameObject>> objects)
{
    for(auto& obj : objects)
    {
        AddObject(obj.first, obj.second);
    }
    camera.SetOrthoProjMat(0.0f, 800.0f, 0.0f, 800.0f, -1.0f, 1.0f);

}

Level::~Level()
{

}

void Level::LoadLevel(std::string filepath)
{

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

/*
void Level::UpdatePhysics(PhysicsSystem& physics, float dt)
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
}
*/
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