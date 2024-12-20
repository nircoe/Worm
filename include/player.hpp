#pragma once

#include "raylib-cpp.hpp"
#include "game_object.hpp"
#include "moveable.hpp"
#include "food.hpp"
#include "auxiliary/consts.hpp"
#include "auxiliary/utils.hpp"
#include "auxiliary/enums.hpp"
#include "auxiliary/colors.hpp"
#include <list>

class Player : public GameObject 
{
    Moveable m_moveable; 
    Enums::Difficulty m_difficulty;

    int m_beginningFrames;
    bool m_isBeginning;

    std::list<raylib::Vector2> m_playerBody; // each item is the center position of a circle

    const bool checkBodyToBodyCollision() const;
    const bool checkBodyToBorderCollision() const;
    raylib::Vector2 fixGettingOffScreen(raylib::Vector2 pos) const;

public:
    Player(raylib::Vector2 initialPosition, const float speed, Enums::Difficulty difficulty);

    virtual ~Player() override = default;

    virtual void update() override;

    virtual void render() const override;

    const bool checkFoodCollision(Food& food) const;

    const raylib::Vector2 getHeadPosition() const;

    const int getScore() const;

    void handleFoodCollision();

    const std::list<raylib::Vector2> getPlayerBody() const;
};
