#pragma once

#include "raylib-cpp.hpp"
#include "game_object.hpp"
#include "moveable.hpp"
#include "food.hpp"
#include "auxiliary/consts.hpp"
#include "auxiliary/utils.hpp"
#include "auxiliary/enums.hpp"
#include "auxiliary/colors.hpp"
#include <deque>

class Player : public GameObject 
{
protected:
    Moveable m_moveable; 
    Enums::Difficulty m_difficulty;

    int m_beginningFrames;
    bool m_isBeginning;

    std::deque<raylib::Vector2> m_playerBody; // each item is the center position of a circle

    const bool checkBodyToBodyCollision() const;
    const bool checkBodyToBorderCollision() const;
    raylib::Vector2 fixGettingOffScreen(raylib::Vector2 pos) const;
    void updatePlayerBody(bool checkInnerCollisions = true);

public:
    Player() = delete;
    
    Player(raylib::Vector2 initialPosition, const float speed, Enums::Difficulty difficulty);

    virtual ~Player() override = default;

    virtual void update() override;

    virtual void render() const override;

    const bool checkFoodCollision(Food& food) const;

    const raylib::Vector2 getHeadPosition() const;

    const std::size_t getScore() const;

    void handleFoodCollision();

    void changeDifficulty(Enums::Difficulty newDifficulty);

    const std::deque<raylib::Vector2> getPlayerBody() const;

    const bool isBeginning() const;
};
