#pragma once
#include <Engine/Scene/GameObject.h>

class Player : public GameObject {

public:
    Player();
    ~Player();

    void OnEvent(const Input& input) override;
    void Update(const Input& input, float dt) override;
    void Render(Renderer& renderer, glm::mat4 projection, const Camera& camera) override;

    void Jump();

    //glm::vec3 velocity{0.0f};
    glm::vec3 gravity{0.0f, -981.0f, 0.0f};

    bool jumping;
    bool alive = true;

};