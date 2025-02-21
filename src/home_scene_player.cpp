#include "home_scene_player.hpp"
#include "game_manager.hpp"

HomeScenePlayer::HomeScenePlayer(raylib::Vector2 initialPosition, const float speed, Enums::Difficulty difficulty) : 
    Player(initialPosition, speed, difficulty)
{
    m_moveable.setVelocity({ Consts::PLAYER_SPEED });
}

void HomeScenePlayer::update()
{
    updatePlayerBody(false);
}

void HomeScenePlayer::loading(GameManager& gameManager)
{
    // get medium level velocity
    raylib::Vector2 velocity = m_moveable.getVelocity();
    if(!velocity.Equals(raylib::Vector2::Zero()))
    {
        if(m_reachedTheCenterOnLoading)
        {
            if(gameManager.getCameraTarget().x >= Consts::SCREEN_WIDTH)
                velocity = raylib::Vector2::Zero();
            m_playerBody.pop_back();
            m_playerBody.push_front(m_playerBody.front() + velocity);
            gameManager.moveCamera(velocity);
        }
        else
        {
            auto frontX = m_playerBody.front().x;
            auto halfScreenX = Consts::HALF_SCREEN.x;
            if(frontX <= halfScreenX && halfScreenX <= frontX + velocity.x)
                m_reachedTheCenterOnLoading = true;
            updatePlayerBody(false);
        }
    }
    // TODO: finish the animation
}

void HomeScenePlayer::resetBody()
{
    m_playerBody = Consts::INITIAL_PLAYER_BODY;
    m_reachedTheCenterOnLoading = false;
}

bool HomeScenePlayer::isFinishLoading() const
{
    return m_playerBody.front().Equals(m_playerBody.back());
}
