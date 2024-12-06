#include "player.hpp"

Player::Player(raylib::Vector2 initialPosition, const float speed)
    : GameObject(initialPosition) 
{
    m_moveable = Moveable(speed);

    m_playerBody = Consts::INITIAL_PLAYER_BODY;
}

void Player::render() const
{
    if(!this->isActive()) return;

    for(int i = 0; i < m_playerBody.size(); ++i)
    {
        float radius = (i == 0) ? 
                        Consts::PLAYER_HEAD_RADIUS : 
                        Consts::PLAYER_BODY_RADIUS;
        DrawCircleV(m_playerBody[i], radius, BROWN);
    }
}

void Player::update() 
{    
    raylib::Vector2 velocity = raylib::Vector2();
    float speed = m_moveable.getSpeed();
    velocity.x = (IsKeyDown(KEY_RIGHT)) ?
                    1.0f : (IsKeyDown(KEY_LEFT)) ?
                    -1.0f : 0;
    velocity.y = (IsKeyDown(KEY_DOWN)) ?
                    1.0f : (IsKeyDown(KEY_UP)) ?
                    -1.0f : 0;                    
    if(velocity.x != 0 || velocity.y != 0)
        velocity = velocity.Normalize();
    velocity *= speed;
    m_moveable.setVelocity(velocity);

    // update the player body positions

    for(size_t i = m_playerBody.size() - 1; i > 0; --i)
    {
        m_playerBody[i] = m_playerBody[i - 1];
    }
    m_playerBody[0] += velocity;
}

const bool Player::checkFoodCollision(const Food& food) const
{
    raylib::Vector2 food_pos = food.getTransform().getPosition();
    raylib::Vector2 food_size = Utils::getFoodSize();
    Rectangle rec = { food_pos.x, food_pos.y, food_size.x, food_size.y };
    return CheckCollisionCircleRec(m_playerBody[0], 10.0f, rec);
}