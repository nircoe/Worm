#pragma once

#include "raylib-cpp.hpp"
#include "game_object.hpp"
#include "moveable.hpp"
#include "food.hpp"
#include "auxiliary/consts.hpp"
#include "auxiliary/utils.hpp"

class Player : public GameObject 
{
public:
    Player(raylib::Vector2 initialPosition, const float speed);

    virtual ~Player() override = default;

    virtual void update() override;

    virtual void render() const override;

    const bool checkFoodCollision(Food& food) const;

private:
    Moveable m_moveable; 

    std::vector<raylib::Vector2> m_playerBody; // each item is the center position of a circle

    const std::vector<raylib::Vector2> getPlayerBody() const;

    const bool checkBodyToBodyCollision() const;
};
