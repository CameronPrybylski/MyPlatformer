#pragma once

#include <Engine/Scene/GameObject.h>

class Obstacle : public GameObject {

public:
    Obstacle(glm::vec3 position, glm::vec3 scale, glm::vec3 velocity, glm::vec4 color, std::string texturePath, bool isStatic);
    ~Obstacle();

    void OnEvent(const Input& input) override;
    void Update(const Input& input, float dt) override;
    void Render(Renderer& renderer, const Camera& camera) override;

    //glm::vec3 velocity{0.0f};


};