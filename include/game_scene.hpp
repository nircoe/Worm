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
#include "ui/text.hpp"

class GameScene : public Scene
{
    Player m_player;
    Food m_food;

    Enums::Difficulty m_difficulty;
    std::vector<raylib::Rectangle> m_borders;
    raylib::Color m_borderColor;

    UI::Text m_startText;
    UI::Text m_gameoverText;
    UI::Text m_scoreText;
    UI::Text m_highscoreText;

    std::array<UI::Button, 3> m_buttons;
    Enums::GameButton m_currentClickedButton = Enums::GameButton::None;

    bool m_isBeginning;
    bool m_gameOver;
    std::size_t m_score = 0;

    virtual raylib::Color checkButton(GameManager &gameManager, const raylib::Color &hoverColor,
                                      const raylib::Color &clickedColor, std::size_t buttonId) override;

    void restart();

    void resetButtonsColor();

    void resetScoreText(GameManager &gameManager);

    void saveGame(GameManager &gameManager);

public:
    GameScene() = default;

    GameScene(Enums::Difficulty difficulty);

    ~GameScene() = default;

    virtual void initUI(const GameManager &gameManager) override;
    virtual void update(GameManager& gameManager) override;
    virtual void render() override;
    virtual void renderUI(const raylib::Camera2D& camera) override;

    const raylib::Vector2 getPlayerHeadPosition() const;

    void changeDifficulty(Enums::Difficulty newDifficulty);

    Enums::Difficulty getDifficulty() const;
};
