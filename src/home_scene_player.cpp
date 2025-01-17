#include "home_scene_player.hpp"

HomeScenePlayer::HomeScenePlayer(raylib::Vector2 initialPosition, const float speed, Enums::Difficulty difficulty) : 
    Player(initialPosition, speed, difficulty)
{
    m_moveable.setVelocity({ Consts::PLAYER_SPEED, 0.0f});
}

void HomeScenePlayer::update()
{
    this->updatePlayerBody(false);
}
