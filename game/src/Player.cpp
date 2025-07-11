#include <Game/Player.h>

Player::Player()
{
    mesh = AssetManager::GetMesh("quadMesh");
    shaderName = "objectShader";
    transform.position = {150.0f, 25.0f, 0.0f};
    transform.scale = {50.0f, 50.0f, 50.0f};
    rigidBody.isStatic = false;
}

Player::~Player()
{

}

void Player::OnEvent(const Input& input)
{
    if(input.IsKeyDown("D") && !jumping)
    {
        rigidBody.velocity.x = 300.0f;
    }
    else if(input.IsKeyDown("A") && !jumping)
    {
        rigidBody.velocity.x = -300.0f;
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

void Player::Update(const Input& input, float dt)
{
    //std::cout << rigidBody.velocity.y << std::endl;   
    
    //std::cout << "Player x velocity " << rigidBody.velocity.x << std::endl;
    //std::cout << "Player y velocity " << rigidBody.velocity.y << std::endl;
    //std::cout << "Player y position " << transform.position.y << std::endl;

    
    if(rigidBody.velocity.y == 0 && jumping)
    {
        jumping = false;
        if(!(input.IsKeyDown("D") || input.IsKeyDown("A")))
        {
            rigidBody.velocity.x = 0;
        }
    }if(transform.position.y >= 800)
    {
        transform.position.y = 800.0f;
    }if(transform.position.y < 0.0f){
        alive = false;
    }
}

void Player::Render(Renderer& renderer, glm::mat4 projection, const Camera& camera)
{
    renderer.DrawQuad(*mesh, transform, camera, AssetManager::GetShader(shaderName), projection, {1.0f, 0.0f, 1.0f, 1.0f});
}

void Player::Jump()
{
    rigidBody.velocity = {rigidBody.velocity.x, 700.0f, 0.0f};
}
