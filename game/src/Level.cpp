#include <Game/Level.h>
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
    player = nullptr;
    //std::cout << j["levelParams"]["completionDist"] << std::endl;
    completionDist = j["levelParams"]["completionDist"];
    nextLevel = j["levelParams"]["nextLevel"];
    for (const auto& objs : j["objects"].items()) {
        for(const auto& obst : objs.value()){
            std::shared_ptr<GameObject> go;
            std::string name = obst.value("name", "Unnamed");
            glm::vec3 position = { obst["position"][0], obst["position"][1], obst["position"][2]};
            glm::vec3 scale = { obst["scale"][0], obst["scale"][1], obst["scale"][2]};
            glm::vec3 velocity = { obst["velocity"][0], obst["velocity"][1], obst["velocity"][2]};
            glm::vec4 color = { obst["color"][0], obst["color"][1], obst["color"][2], obst["color"][3]};
            bool isStatic = obst.value("isStatic", false);
            std::string texturePath = obst.value("texturePath", "Unnamed");
            
            if(objs.key() == "obstacles"){
                go = std::make_shared<Obstacle>(position, scale, velocity, color, "", name, isStatic);
                AddObject(obst.value("name", "Unnamed"), go);
            }
            else if(objs.key() == "floor"){
                go = std::make_shared<Floor>(position, scale, color, "", name, isStatic);
                AddObject(obst.value("name", "Unnamed"), go);
            }
            else if(objs.key() == "player"){
                player = std::make_shared<Player>(position, scale, color, texturePath, name, isStatic);
                go = player;
                AddObject(obst.value("name", "Unnamed"), go);
            }
            else if(objs.key() == "enemies"){
                std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(position, scale, velocity, color, "", name, isStatic);
                go = enemy;
                AddObject(obst.value("name", "Unnamed"), go);
                enemies.push_back(enemy);
            }
        }
    }
    
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
    std::vector<CollisionEvent> collisions = physics.Update(dt);
    OnCollision(physics, collisions, dt);


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
    if(player->transform.position.x + player->transform.scale.x >= completionDist){
        EndScene(nextLevel);
    }
}

void Level::OnCollision(PhysicsSystem& physics, std::vector<CollisionEvent> collisions, float dt)
{
    for(auto& collision : collisions)
    {
        //std::cout << collision.body1.transform->position.x << " " << collision.body2.transform->position.x << std::endl;
        if((*collision.body1.transform == player->transform || *collision.body2.transform == player->transform) && !player->hit)
        {
            glm::vec2 normalBody1;
            glm::vec2 normalBody2;
            if(*collision.body1.transform == player->transform)
            {
                //normal = physics.GetCollisionNormal(player->transform, *collision.body2.transform);
            }else{
                //normal = physics.GetCollisionNormal(player->transform, *collision.body1.transform);
            }

            // Player lands on top
            //if(normal.x == 0 && normal.y == 1)
            {
                for(auto& obj : objectList)
                {
                    if(obj != player && (*collision.body1.transform == obj->transform || *collision.body2.transform == obj->transform))
                    {
                        if(*collision.body1.transform == obj->transform)
                        {
                            normalBody1 = collision.collisionNormalBody1;
                            normalBody2 = collision.collisionNormalBody2;
                        }
                        if(*collision.body2.transform == obj->transform)
                        {
                            normalBody1 = collision.collisionNormalBody2;
                            normalBody2 = collision.collisionNormalBody1;
                        }
                        obj->OnCollision(player, normalBody1, dt);
                        player->OnCollision(obj, normalBody2, dt);
                    }
                }
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