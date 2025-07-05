#include <Game/Obstacle.h>

Obstacle::Obstacle()
{
    shaderName = "objectShader";
    mesh = AssetManager::GetMesh("quadMesh");
    transform.position = {750.0f, 25.0f, 0.0f};
    transform.scale = {50.0f, 50.0f, 0.0f};
    rigidBody.velocity.x = -500.0f;
    rigidBody.isStatic = false;
}

Obstacle::~Obstacle()
{
}

void Obstacle::OnEvent(const Input &input)
{
}

void Obstacle::Update(float dt)
{
    transform.position.x += rigidBody.velocity.x * dt;
    if(transform.position.x < 0.0f)
    {
        rigidBody.velocity *= -1;
    }
    if(transform.position.x > 800.0f)
    {
        rigidBody.velocity *= -1;
    }
}

void Obstacle::Render(Renderer &renderer, glm::mat4 projection)
{
    renderer.DrawQuad(*mesh, transform, AssetManager::GetShader(shaderName), projection, {1.0, 0.0f, 0.0f, 1.0f});
}
