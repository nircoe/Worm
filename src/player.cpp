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
    raylib::Vector2 prevVelocity = this->m_moveable.getVelocity();
    raylib::Vector2 velocity = raylib::Vector2();
    float speed = this->m_moveable.getSpeed();
    velocity.x = (IsKeyDown(KEY_RIGHT)) ?
                    Consts::ONE_F : (IsKeyDown(KEY_LEFT)) ?
                    -Consts::ONE_F : Consts::ZERO_F;
    velocity.y = (IsKeyDown(KEY_DOWN)) ?
                    Consts::ONE_F : (IsKeyDown(KEY_UP)) ?
                    -Consts::ONE_F : Consts::ZERO_F;                    
    if(velocity.x != 0 || velocity.y != 0)
        velocity = velocity.Normalize();
    velocity *= speed;
    if(velocity == Consts::ZERO_2D || velocity == -prevVelocity) 
        velocity = prevVelocity;
    m_moveable.setVelocity(velocity);

    // update the player body positions
    if(velocity != Consts::ZERO_2D)
    {
        for(size_t i = m_playerBody.size() - 1; i > 0; --i)
        {
            m_playerBody[i] = m_playerBody[i - 1];
        }
        m_playerBody[0] += velocity;
    }
}

const bool Player::checkFoodCollision(Food& food) const
{
    raylib::Vector2 food_pos = food.getTransform().getPosition();
    raylib::Vector2 food_size = Utils::getFoodSize();
    Rectangle rec = { food_pos.x, food_pos.y, food_size.x, food_size.y };
    bool res = CheckCollisionCircleRec(m_playerBody[0], 10.0f, rec);
    if(res) food.changePosition(Utils::getFoodSpawnPoint(this->getPlayerBody()));
    return res;
}

const std::vector<raylib::Vector2> Player::getPlayerBody() const
{
    return this->m_playerBody;
}
