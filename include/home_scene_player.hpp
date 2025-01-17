#pragma once

#include "player.hpp"

class HomeScenePlayer : public Player
{
public:
    HomeScenePlayer() = delete;
    
    HomeScenePlayer(raylib::Vector2 initialPosition, const float speed, Enums::Difficulty difficulty);

    virtual ~HomeScenePlayer() override = default;

    virtual void update() override;
};