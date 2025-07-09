#include <Game/Floor.h>

Floor::Floor()
{
    mesh = AssetManager::GetMesh("quadMesh");
    shaderName = "objectShader";
    transform.position = {0.5f, 25.0f, 0.0f};
    transform.scale = {1600.0f, 50.0f, 0.0f};
    rigidBody.isStatic = true;
}

Floor::~Floor()
{

}

void Floor::OnEvent(const Input& input)
{

}

void Floor::Update(float dt)
{

}

void Floor::Render(Renderer& renderer, glm::mat4 projection)
{
    renderer.DrawQuad(*mesh, transform, AssetManager::GetShader(shaderName), projection, {0.0f, 1.0f, 0.0f, 0.5f});
}