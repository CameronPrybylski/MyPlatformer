#include <Game/Player.h>

Player::Player(glm::vec3 position, glm::vec3 scale, glm::vec4 color, std::string texturePath, std::string name, bool isStatic)
{
    mesh = AssetManager::GetMesh("quadMesh");
    shaderName = "textureShader";
    transform.position = position;
    transform.scale = scale;
    rigidBody.isStatic = isStatic;
    hp = 2;
    texture.Create("/Users/cameronprzybylski/Documents/C++/C++ Projects/MyPlatformer/textures/Mario-8bit.png");
    this->color = color;
    this->name = name;
}

Player::~Player()
{

}

void Player::OnEvent(const Input& input)
{
    if(input.IsKeyDown("D") && !jumping && !hit)
    {
        rigidBody.velocity.x = 300.0f;
        if(input.IsKeyDown("C"))
        {
            rigidBody.velocity.x = 600.0f;
        }
    }
    else if(input.IsKeyDown("A") && !jumping && !hit)
    {
        rigidBody.velocity.x = -300.0f;
        if(input.IsKeyDown("C"))
        {
            rigidBody.velocity.x = -600.0f;
        }
    }
    else if(!jumping && !riding){
        rigidBody.velocity.x = 0;
    }
    if(input.IsKeyDown("SPACE") && !jumping && !hit)
    {
        riding = false;
        jumping = true;
        Jump();
    }
    if(input.IsLeftMouseButtonDown() && !jumping)
    {
        jumping = true;
        Jump();
    }

}

void Player::Update(const Input& input, float dt)
{
    if(rigidBody.velocity.y == 0 && jumping)
    {
        jumping = false;
        if(!(input.IsKeyDown("D") || input.IsKeyDown("A")))
        {
            rigidBody.velocity.x = 0;
        }
        hit = false;
    }else{
        if(input.IsKeyDown("D") && !jumping && !hit)
        {
            riding = false;
            rigidBody.velocity.x = 300.0f;
            if(input.IsKeyDown("C"))
            {
                rigidBody.velocity.x = 600.0f;
            }
        }
        else if(input.IsKeyDown("A") && !jumping && !hit)
        {
            riding = false;
            rigidBody.velocity.x = -300.0f;
            if(input.IsKeyDown("C"))
            {
                rigidBody.velocity.x = -600.0f;
            }
        }
    }
    if(transform.position.y >= 800)
    {
        //transform.position.y = 800.0f;
    }if(transform.position.y < 0.0f || hp <= 0){
        alive = false;
    }
    if(transform.position.x - transform.scale.x / 2 < 0.0f){
        transform.position.x = 0.0f + transform.scale.x / 2;
    }
}

void Player::OnCollision(std::shared_ptr<GameObject> collidedObj, glm::vec2 collisionNormal, float dt)
{
    if(collisionNormal.x == 0 && collisionNormal.y == 1)
    {
        if(collidedObj->name.find("obstacle") != std::string::npos)
        {
            riding = true;
        }
    }
    else if (collidedObj->name.find("enemy") != std::string::npos && !hit)
    {
        Hit(dt);
    }
}

void Player::Render(Renderer& renderer, const Camera& camera)
{
    renderer.DrawTexturedQuad(*mesh, transform, camera, AssetManager::GetShader(shaderName), texture, color);
    texture.Unbind();
}

void Player::Jump()
{
    rigidBody.velocity = {rigidBody.velocity.x, 1000.0f, 0.0f};
}

void Player::Hit(float dt)
{
    rigidBody.velocity.x *= -1;
    jumping = true;
    hit = true;
    hp--;
    Jump();
}
