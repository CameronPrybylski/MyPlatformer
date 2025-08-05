#include <Game/Floor.h>

Floor::Floor()
{
    mesh = AssetManager::GetMesh("quadMesh");
    shaderName = "objectShader";
    transform.position = {800.0f, 25.0f, 0.0f};
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

void Floor::Render(Renderer& renderer, const Camera& camera)
{
    renderer.DrawQuad(*mesh, transform, camera, AssetManager::GetShader(shaderName), {0.0f, 1.0f, 0.0f, 0.5f});
}