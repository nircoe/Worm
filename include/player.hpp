#pragma once

#include "raylib-cpp.hpp"
#include "game_object.hpp"
#include "moveable.hpp"

class Player : public GameObject 
{
public:
    Player(raylib::Vector2 initialPosition, const float speed);

    virtual ~Player() override = default;

    virtual void Update() override;

    virtual void Render() const override;

private:
    Moveable m_moveable; 

    std::vector<raylib::Vector2> m_playerBody; // each item is the center position of a circle
};
