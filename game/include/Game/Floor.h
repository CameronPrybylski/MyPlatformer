#pragma once

#include <Engine/Scene/GameObject.h>

class Floor : public GameObject {

public:
    Floor(glm::vec3 position, glm::vec3 scale, glm::vec4 color, std::string texturePath, std::string name, bool isStatic);
    ~Floor();
    void OnEvent(const Input& input) override;
    void Update(float dt) override;
    void Render(Renderer& renderer, const Camera& camera) override;

};