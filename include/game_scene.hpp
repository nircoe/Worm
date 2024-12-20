#pragma once

#include <vector>
#include "scene.hpp"
#include "game_object.hpp"
#include "player.hpp"
#include "food.hpp"
#include "auxiliary/consts.hpp"
#include "auxiliary/utils.hpp"
#include "auxiliary/enums.hpp"
#include "auxiliary/colors.hpp"

class GameScene : public Scene
{
    Player m_player;
    Food m_food;

    Enums::Difficulty m_difficulty;
    const std::vector<raylib::Rectangle> m_borders;

    bool m_gameOver;
    
    const int GAME_OVER_TEXT_WIDTH = Utils::centerlizeTextX(Consts::GAME_OVER_TEXT.c_str(), Consts::GAME_OVER_FONT_SIZE);

    void gameOver() const;

public:
    GameScene(Enums::Difficulty difficulty);

    ~GameScene() = default;
    
    void update() override;
    void render() override;

    const raylib::Vector2 getPlayerHeadPosition() const;
};
