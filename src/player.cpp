#include "player.hpp"

Player::Player(raylib::Vector2 initialPosition, const float speed)
    : GameObject(initialPosition) 
{
    m_moveable = Moveable(speed);
}

void Player::Render() const
{
    for(const auto& it : m_playerBody)
    {
        DrawCircle(it.x, it.y, 10.0f, BROWN);
    }
}

void Player::Update() 
{    
    raylib::Vector2 velocity = raylib::Vector2();
    float speed = m_moveable.getSpeed();
    velocity.x = (IsKeyDown(KEY_RIGHT)) ?
                    1 : (IsKeyDown(KEY_LEFT)) ?
                    -1 : 0;
    velocity.y = (IsKeyDown(KEY_DOWN)) ?
                    1 : (IsKeyDown(KEY_UP)) ?
                    -1 : 0;                    
    if(velocity.x != 0 || velocity.y != 0)
        velocity = velocity.Normalize();
    velocity *= speed;
    m_moveable.setVelocity(velocity);

    // update the player body positions

    for(int i = m_playerBody.size() - 1; i > 0; --i)
    {
        m_playerBody[i] = m_playerBody[i - 1];
    }
    m_playerBody[0] += velocity;
}
