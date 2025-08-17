#include <Game/Enemy.h>

Enemy::Enemy(glm::vec3 position, glm::vec3 scale, glm::vec3 velocity, glm::vec4 color, std::string texturePath, std::string name, bool isStatic)
{
    
    mesh = AssetManager::GetMesh("quadMesh");
    transform.position = position;
    transform.scale = scale;
    rigidBody.velocity = velocity;
    rigidBody.isStatic = isStatic;
    this->color = color;
    this->isAlive = true;
    this->name = name;
    this->type = "Enemy";
    this->velocity = velocity;
    if(texturePath != ""){
        shaderName = "textureShader";
        texture.Create(texturePath);
    }else{
        shaderName = "objectShader";
    }
}

Enemy::~Enemy()
{
}

void Enemy::OnEvent(const Input &input)
{
}

void Enemy::Update(float dt)
{
    std::cout << transform.position.x << std::endl;
    if(transform.position.x < 700.0f)
    {
        rigidBody.velocity.x *= -1;
    }
    if(transform.position.x > 800.0f)
    {
        rigidBody.velocity.x *= -1;
    }
}

void Enemy::Update(const Input &input, float dt)
{
    if(transform.position.x - transform.scale.x / 2 < 0.0f)
    {
        //rigidBody.velocity.x *= -1;
    }
    if(transform.position.x > 800.0f)
    {
        //rigidBody.velocity.x *= -1;
    }
    if(!isAlive)
    {
        transform.position.y = -500.0f;
    }
}
void Enemy::OnCollision(std::shared_ptr<GameObject> collidedObj, glm::vec2 collisionNormal, float dt)
{
    if(collisionNormal.x == 0 && collisionNormal.y == -1)
    {
        if(collidedObj->name.find("player") != std::string::npos)
        {
            isAlive = false;
        }
    }
    if(collisionNormal.x == 1 && collisionNormal.y == 0)
    {
        rigidBody.velocity.x = abs(velocity.x);
    }
    if(collisionNormal.x == -1 && collisionNormal.y == 0)
    {
        rigidBody.velocity.x = -abs(velocity.x);
    }
}

void Enemy::Render(Renderer &renderer, const Camera &camera)
{
    if(isAlive)
    {
        if(shaderName == "textureShader"){
            renderer.DrawTexturedQuad(*mesh, transform, camera, AssetManager::GetShader(shaderName), texture, color);
        }else{
            renderer.DrawQuad(*mesh, transform, camera, AssetManager::GetShader(shaderName), color);
        }
    }
}

