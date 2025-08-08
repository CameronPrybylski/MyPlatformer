#include <Game/Player.h>

Player::Player(glm::vec3 position, glm::vec3 scale, glm::vec4 color, std::string texturePath, bool isStatic)
{
    mesh = AssetManager::GetMesh("quadMesh");
    shaderName = "textureShader";
    transform.position = position;
    transform.scale = scale;
    rigidBody.isStatic = isStatic;
    hp = 3;
    texture.Create("/Users/cameronprzybylski/Documents/C++/C++ Projects/MyPlatformer/textures/Mario-8bit.png");
}

Player::~Player()
{

}

void Player::OnEvent(const Input& input)
{
    if(input.IsKeyDown("D") && !jumping && !hit)
    {
        rigidBody.velocity.x = 300.0f;
    }
    else if(input.IsKeyDown("A") && !jumping && !hit)
    {
        rigidBody.velocity.x = -300.0f;
    }
    else if(!jumping){
        rigidBody.velocity.x = 0;
    }
    if(input.IsKeyDown("SPACE") && !jumping && !hit)
    {
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
    }if(transform.position.y >= 800)
    {
        transform.position.y = 800.0f;
    }if(transform.position.y < 0.0f){
        alive = false;
    }
    if(transform.position.x - transform.scale.x / 2 < 0.0f){
        transform.position.x = 0.0f + transform.scale.x / 2;
    }
}

void Player::OnCollision(float dt)
{
    Hit(dt);
}

void Player::Render(Renderer& renderer, const Camera& camera)
{
    renderer.DrawTexturedQuad(*mesh, transform, camera, AssetManager::GetShader(shaderName), texture, {1.0f, 1.0f, 1.0f, 0.0f});
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
    hp -= dt;
    Jump();
}
