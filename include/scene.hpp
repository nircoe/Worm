#pragma once

#include <vector>
#include "game_object.hpp"
#include "player.hpp"
#include "food.hpp"
#include "auxiliary/consts.hpp"
#include "auxiliary/utils.hpp"

class Scene 
{
public:
    Scene();

    ~Scene() = default;
    
    void update();
    void render();

    const raylib::Vector2 getPlayerHeadPosition() const;

private:
    Player m_player;
    Food m_food;

    bool m_gameOver;
    const int GAME_OVER_TEXT_WIDTH = Utils::centerlizeTextX(Consts::GAME_OVER_TEXT.c_str(), Consts::GAME_OVER_FONT_SIZE);

    void gameOver() const;
};
