#pragma once

#include <Engine/Scene/GameObject.h>

class Obstacle : public GameObject {

public:
    Obstacle();
    ~Obstacle();

    void OnEvent(const Input& input) override;
    void Update(float dt) override;
    void Render(Renderer& renderer, glm::mat4 projection) override;

    //glm::vec3 velocity{0.0f};


};