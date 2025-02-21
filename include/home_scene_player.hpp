#pragma once

#include "player.hpp"

class GameManager;

class HomeScenePlayer : public Player
{
    bool m_reachedTheCenterOnLoading = false;

public:
    HomeScenePlayer() = delete;
    
    HomeScenePlayer(raylib::Vector2 initialPosition, const float speed, Enums::Difficulty difficulty);

    virtual ~HomeScenePlayer() override = default;

    virtual void update() override;

    void loading(GameManager& gameManager);

    void resetBody();

    bool isFinishLoading() const;
};