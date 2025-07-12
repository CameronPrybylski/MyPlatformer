#pragma once

#include <Engine/Scene/Scene.h>

class GameOver : public Scene {
public:
    GameOver(){}
    ~GameOver(){}
    void OnUpdate(const Input& input, PhysicsSystem& physics, float dt) override;
};