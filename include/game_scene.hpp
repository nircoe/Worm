#pragma once

#include <vector>
#include <array>
#include <string>
#include "game_manager.hpp"
#include "scene.hpp"
#include "game_object.hpp"
#include "player.hpp"
#include "food.hpp"
#include "auxiliary/consts.hpp"
#include "auxiliary/utils.hpp"
#include "auxiliary/enums.hpp"
#include "auxiliary/colors.hpp"
#include "ui/button.hpp"

class GameScene : public Scene
{
    Player m_player;
    Food m_food;

    Enums::Difficulty m_difficulty;
    std::vector<raylib::Rectangle> m_borders;
    raylib::Color m_borderColor;

    const std::string m_startText = "Start Moving With The Arrow Buttons!";
    std::string m_scoreText;
    raylib::Vector2 m_startTextPosition;
    raylib::Vector2 m_gameOverTextPosition;
    raylib::Vector2 m_scoreTextPosition;

    std::array<UI::Button, 3> m_buttons;
    Enums::GameButton m_currentClickedButton = Enums::GameButton::None;

    bool m_isBeginning;
    bool m_gameOver;
    std::size_t m_score = 0;
    
    const int GAME_OVER_TEXT_WIDTH = Utils::centerlizeTextX(Consts::GAME_OVER_TEXT.c_str(), Consts::GAME_OVER_FONT_SIZE);

    virtual raylib::Color checkButton(GameManager& gameManager, const raylib::Color &hoverColor, 
        const raylib::Color& clickedColor, int buttonId) override; 

    void gameOver(const raylib::Font& font) const;

    void restart();

    void resetButtonsColor();

    void resetScoreText(const raylib::Font& font);

public:
    GameScene() = default;

    GameScene(Enums::Difficulty difficulty);

    ~GameScene() = default;
    
    virtual void update(GameManager& gameManager) override;
    virtual void render() override;
    virtual void renderUI(const raylib::Font& font, const raylib::Camera2D& camera) override;

    const raylib::Vector2 getPlayerHeadPosition() const;

    void changeDifficulty(Enums::Difficulty newDifficulty);

    const Enums::Difficulty getDifficulty() const;

    virtual void initUI(const raylib::Font& font) override;
};
