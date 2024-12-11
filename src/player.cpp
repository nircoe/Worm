#include "player.hpp"

Player::Player(raylib::Vector2 initialPosition, const float speed)
    : GameObject(initialPosition) 
{
    m_moveable = Moveable(speed);

    m_playerBody = Consts::INITIAL_PLAYER_BODY;
}

void Player::render() const
{
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
    if(!this->isActive()) return;

    raylib::Vector2 prevVelocity = this->m_moveable.getVelocity();
    raylib::Vector2 velocity = raylib::Vector2();
    float speed = this->m_moveable.getSpeed();
    velocity.x = (IsKeyDown(KEY_RIGHT)) ?
                    1.0f : (IsKeyDown(KEY_LEFT)) ?
                    -1.0f : 0.0f;
    velocity.y = (IsKeyDown(KEY_DOWN)) ?
                    1.0f : (IsKeyDown(KEY_UP)) ?
                    -1.0f : 0.0f;                    
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
        m_playerBody[0] = Utils::fixGettingOffScreen(m_playerBody[0]);
    }

    if(this->checkBodyToBodyCollision())
    {
        this->setActive(false);
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

const raylib::Vector2 Player::getHeadPosition() const
{
    return this->getPlayerBody()[0];
}

const int Player::getScore() const
{
    return this->getPlayerBody().size() - 3;
}

const std::vector<raylib::Vector2> Player::getPlayerBody() const
{
    return this->m_playerBody;
}

const bool Player::checkBodyToBodyCollision() const
{
    const size_t bodySize = this->getPlayerBody().size();
    for(size_t i = 1; i < bodySize; ++i)
    {
        if(CheckCollisionCircles(this->m_playerBody[0], Consts::PLAYER_HEAD_RADIUS,
                                    this->m_playerBody[i], Consts::PLAYER_BODY_RADIUS))
            return true;
    }
    return false;
}
