#pragma once

#include <Engine/Scene/GameObject.h>

class Floor : public GameObject {

public:
    Floor();
    ~Floor();
    void OnEvent(const Input& input) override;
    void Update(float dt) override;
    void Render(Renderer& renderer, glm::mat4 projection, const Camera& camera) override;

};