#include "player.hpp"

Player::Player(raylib::Vector2 initialPosition, const float speed, Enums::Difficulty difficulty)
    : GameObject(initialPosition), 
        m_moveable(speed), 
        m_difficulty(difficulty), 
        m_beginningFrames(0), 
        m_isBeginning(true), 
        m_playerBody(Consts::INITIAL_PLAYER_BODY)
{ }

void Player::render() const
{
    for (auto it = m_playerBody.rbegin(); it != m_playerBody.rend(); ++it)
    {
        float radius = (m_playerBody.front().Equals(*it)) ? Consts::PLAYER_HEAD_RADIUS : Consts::PLAYER_BODY_RADIUS;
        Color color = (m_playerBody.front().Equals(*it)) ? Colors::WORM_HEAD_COLOR : Colors::WORM_BODY_COLOR;
        DrawCircleV(*it, radius, color);
    }
}

void Player::update() 
{    
    if(!this->isActive()) return;

    raylib::Vector2 prevVelocity = this->m_moveable.getVelocity();
    raylib::Vector2 velocity;
    float speed = this->m_moveable.getSpeed();

    velocity.x = IsKeyDown(KEY_RIGHT) ? 1.0f : (IsKeyDown(KEY_LEFT) ? -1.0f : 0.0f);
    velocity.y = IsKeyDown(KEY_DOWN) ? 1.0f : (IsKeyDown(KEY_UP) ? -1.0f : 0.0f);                    
    if(velocity.x != 0 || velocity.y != 0)
        velocity = velocity.Normalize();
    velocity *= speed;
    if(velocity == raylib::Vector2::Zero() || velocity.Normalize().Equals(-prevVelocity.Normalize())) 
        velocity = prevVelocity;

    // update the player body positions
    if(velocity != raylib::Vector2::Zero())
    {
        raylib::Vector2 temp = velocity;
        if(CheckCollisionCircles(this->fixGettingOffScreen(m_playerBody.front() + velocity), 
                                    Consts::PLAYER_HEAD_RADIUS, *(++m_playerBody.begin()), Consts::PLAYER_BODY_RADIUS))
        {
            velocity *= Consts::DIAGONAL_MULTIPLY;
        }
        m_playerBody.pop_back();
        m_playerBody.push_front(this->fixGettingOffScreen(m_playerBody.front() + velocity));

        if(this->m_beginningFrames < 3)
            if(++(this->m_beginningFrames) == 3)
                this->m_isBeginning = false;
    }

    m_moveable.setVelocity(velocity);

    if(this->checkBodyToBodyCollision() || this->checkBodyToBorderCollision())
        this->setActive(false);
}

const bool Player::checkFoodCollision(Food& food) const
{
    raylib::Vector2 food_pos = food.getTransform().getPosition();
    raylib::Vector2 food_size = Utils::getFoodSize();
    Rectangle rec = { food_pos.x, food_pos.y, food_size.x, food_size.y };
    return CheckCollisionCircleRec(m_playerBody.front(), 10.0f, rec);
}

const raylib::Vector2 Player::getHeadPosition() const
{
    return this->getPlayerBody().front();
}

const int Player::getScore() const
{
    return this->getPlayerBody().size() - 3;
}

void Player::handleFoodCollision()
{
    this->m_playerBody.push_back(raylib::Vector2::Zero());
}

const std::list<raylib::Vector2> Player::getPlayerBody() const
{
    return this->m_playerBody;
}

const bool Player::checkBodyToBodyCollision() const
{
    if(this->m_isBeginning) return false;

    for (auto it = ++(m_playerBody.begin()); it != m_playerBody.end(); ++it)
    {
        if(CheckCollisionCircles(this->m_playerBody.front(), Consts::PLAYER_HEAD_RADIUS,
                                    *it, Consts::PLAYER_BODY_RADIUS))
            return true;
    }
    return false;
}

const bool Player::checkBodyToBorderCollision() const
{
    if(this->m_difficulty != Enums::Difficulty::Hard && 
        this->m_difficulty != Enums::Difficulty::Impossible) return false;

    for (auto &&rec : Consts::BORDERS)
    {
        if(CheckCollisionCircleRec(this->m_playerBody.front(), Consts::PLAYER_HEAD_RADIUS, rec))
            return true;
    }
    return false;
}

raylib::Vector2 Player::fixGettingOffScreen(raylib::Vector2 pos) const
{
    if(this->m_difficulty == Enums::Difficulty::Hard || 
        this->m_difficulty == Enums::Difficulty::Impossible) return pos;

    if(pos.x < 0.0f)
    {
        pos.x += Consts::SCREEN_WIDTH;
    }
    else if(Consts::SCREEN_WIDTH < pos.x)
    {
        pos.x -= Consts::SCREEN_WIDTH;
    }

    if(pos.y < 0.0f)
    {
        pos.y += Consts::SCREEN_HEIGHT;
    }
    else if(Consts::SCREEN_HEIGHT < pos.y)
    {
        pos.y -= Consts::SCREEN_HEIGHT;
    }
    return pos;
}
