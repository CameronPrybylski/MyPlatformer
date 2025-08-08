#pragma once

#include <Engine/Scene/Scene.h>
#include <Game/Player.h>

class Level : public Scene {

public:
    Level(float screenWidth, float screenHeight, std::string filepath);
    //Level(std::unordered_map<std::string, std::shared_ptr<GameObject>> objects);
    ~Level();

    void Init() override;

    void LoadLevel(std::string filepath);
    void LoadPhysics(PhysicsSystem& physics) override;
    void OnEvent(const Input& input) override;
    void OnUpdate(const Input& input, PhysicsSystem& physics, float dt) override;
    void OnCollision(std::vector<CollisionEvent> collisions, float dt);

    //void UpdatePhysics(PhysicsSystem& physics, float dt);

    void UpdateCamera();

private:
    float leftScreenEdge;
    float rightScreenEdge;
    std::shared_ptr<Player> player;
    bool gameOver = false;
    std::string filepath;


};