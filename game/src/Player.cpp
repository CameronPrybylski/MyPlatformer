#include <Game/Player.h>

Player::Player()
{
    mesh = AssetManager::GetMesh("quadMesh");
    shaderName = "objectShader";
    transform.position = {75.0f, 0.0f, 0.0f};
    transform.scale = {50.0f, 50.0f, 50.0f};
    rigidBody.isStatic = false;
}

Player::~Player()
{

}

void Player::OnEvent(const Input& input)
{
    std::string keys[4] = {"W", "A", "S", "D"};

    if(input.IsKeyDown("D"))
    {
        rigidBody.velocity.x = 500.0f;
    }
    else if(input.IsKeyDown("A"))
    {
        rigidBody.velocity.x = -500.0f;
    }
    else if(!jumping){
        rigidBody.velocity.x = 0;
    }
    if(input.IsKeyDown("SPACE") && !jumping)
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

void Player::Update(float dt)
{
    
    std::cout << rigidBody.velocity.x << std::endl;
    rigidBody.velocity += gravity * dt;
    transform.position += rigidBody.velocity * dt;
    
    if(transform.position.y <= 25.0f)
    {
        rigidBody.velocity.y = 0.0f;
        //rigidBody.velocity.x = 0.0f;
        transform.position.y = 25.0f;
        jumping = false;
    }if(transform.position.y >= 800){
        rigidBody.velocity.y = 0.0f;
        //rigidBody.velocity.x = 0.0f;
        transform.position.y = 800.0f;
        jumping = false;
    }
}

void Player::Render(Renderer& renderer, glm::mat4 projection)
{
    renderer.DrawQuad(*mesh, transform, AssetManager::GetShader(shaderName), projection, {1.0f, 0.0f, 1.0f, 1.0f});
}

void Player::Jump()
{
    rigidBody.velocity = {rigidBody.velocity.x, 500.0f, 0.0f};
}
