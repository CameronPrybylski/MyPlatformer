#include <Game/Obstacle.h>

Obstacle::Obstacle(glm::vec3 position, glm::vec3 scale, glm::vec3 velocity, glm::vec4 color, std::string texturePath, std::string name, bool isStatic)
{
    //shaderName = "textureShader";
    mesh = AssetManager::GetMesh("quadMesh");
    transform.position = position;
    transform.scale = scale;
    rigidBody.velocity = velocity;
    rigidBody.isStatic = isStatic;
    this->color = color;
    this->name = name;
    if(texturePath != ""){
        shaderName = "textureShader";
        texture.Create(texturePath);
    }else{
        shaderName = "objectShader";
    }
    //texture.Create("/Users/cameronprzybylski/Documents/C++/C++ Projects/MyPlatformer/textures/GameOver.png");
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
    transform.position.y = 150.0f;
    //if(transform.position.x - transform.scale.x / 2 < 0.0f)
    if(transform.position.x - (transform.scale.x / 2) < 600.0f)
    {
        rigidBody.velocity.x *= -1;
    }
    if(transform.position.x > 1600.0f)
    {
        rigidBody.velocity.x *= -1;
    }
    transform.position.x += rigidBody.velocity.x * dt;
}

void Obstacle::OnCollision(std::shared_ptr<GameObject> collidedObj, glm::vec2 collisionNormal, float dt)
{
    collidedObj->rigidBody.velocity.x = rigidBody.velocity.x;
}

void Obstacle::Render(Renderer &renderer, const Camera& camera)
{
    if(shaderName == "textureShader"){
        renderer.DrawTexturedQuad(*mesh, transform, camera, AssetManager::GetShader(shaderName), texture, color);
    }else{
        renderer.DrawQuad(*mesh, transform, camera, AssetManager::GetShader(shaderName), color);
    }
}