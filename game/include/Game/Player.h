#pragma once
#include <Engine/Scene/GameObject.h>

class Player : public GameObject {

public:
    Player(glm::vec3 position, glm::vec3 scale, glm::vec4 color, std::string texturePath, std::string name, bool isStatic);
    ~Player();

    void OnEvent(const Input& input) override;
    void Update(const Input& input, float dt) override;
    void Render(Renderer& renderer, const Camera& camera) override;
    void OnCollision(std::shared_ptr<GameObject> collidedObj, glm::vec2 collisionNormal, float dt) override;

    void Jump();
    void Hit(float dt);

    //glm::vec3 velocity{0.0f};
    glm::vec3 gravity{0.0f, -981.0f, 0.0f};

    bool jumping;
    bool riding = false;
    bool hit = false;
    bool alive = true;

    int hp;

};