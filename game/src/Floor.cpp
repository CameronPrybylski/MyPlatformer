#include <Game/Floor.h>

Floor::Floor(glm::vec3 position, glm::vec3 scale, glm::vec4 color, std::string texturePath, std::string name, bool isStatic)
{
    mesh = AssetManager::GetMesh("quadMesh");
    shaderName = "objectShader";
    transform.position = position;
    transform.scale = scale;
    rigidBody.isStatic = isStatic;
    this->color = color;
    this->name = name;
}

Floor::~Floor()
{

}

void Floor::OnEvent(const Input& input)
{

}

void Floor::Update(float dt)
{
    transform.position.y = 25.0f;
}

void Floor::Render(Renderer& renderer, const Camera& camera)
{
    renderer.DrawQuad(*mesh, transform, camera, AssetManager::GetShader(shaderName), color);
}