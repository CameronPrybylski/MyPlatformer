#include <Game/Floor.h>

Floor::Floor(glm::vec3 position, glm::vec3 scale, glm::vec4 color, std::string texturePath, bool isStatic)
{
    mesh = AssetManager::GetMesh("quadMesh");
    shaderName = "objectShader";
    transform.position = position;
    transform.scale = scale;
    rigidBody.isStatic = isStatic;
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