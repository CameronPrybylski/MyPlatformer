#include <Game/Level.h>
#include <Game/Player.h>
#include <Game/Obstacle.h>


Level::Level()
{
    std::shared_ptr<GameObject> player = std::make_shared<Player>();
    std::shared_ptr<GameObject> obstacle = std::make_shared<Obstacle>();
    AddObject("player", player);
    AddObject("obstacle_1", obstacle);
    SetOrthoProjMat(0.0f, 800.0f, 0.0f, 800.0f, -1.0f, 1.0f);
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