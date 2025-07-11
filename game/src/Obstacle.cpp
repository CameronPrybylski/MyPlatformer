#include <Game/Obstacle.h>

Obstacle::Obstacle(glm::vec3 position, glm::vec3 scale, glm::vec3 velocity, bool isStatic)
{
    shaderName = "objectShader";
    mesh = AssetManager::GetMesh("quadMesh");
    transform.position = position;
    transform.scale = scale;
    rigidBody.velocity = velocity;
    rigidBody.isStatic = isStatic;
}

Obstacle::~Obstacle()
{
}

void Obstacle::OnEvent(const Input &input)
{
}

void Obstacle::Update(const Input& input, float dt)
{
    //transform.position.x += rigidBody.velocity.x * dt;
    //std::cout << rigidBody.velocity.x << std::endl;
    if(transform.position.x < 0.0f)
    {
        rigidBody.velocity.x *= -1;
    }
    if(transform.position.x > 800.0f)
    {
        rigidBody.velocity.x *= -1;
    }
}

void Obstacle::Render(Renderer &renderer, glm::mat4 projection, const Camera& camera)
{
    renderer.DrawQuad(*mesh, transform, camera, AssetManager::GetShader(shaderName), projection, {1.0, 0.0f, 0.0f, 1.0f});
}
