#pragma once

#include "scene.hpp"
#include "raylib-cpp.hpp"
#include "home_scene_player.hpp"
#include "auxiliary/consts.hpp"
#include "auxiliary/utils.hpp"
#include "auxiliary/enums.hpp"
#include "ui/button.hpp"
#include "ui/text.hpp"
#include <string>

namespace raylib { class Color; class Vector2; class Rectangle; }

class HomeScene : public Scene
{
    UI::Text m_title;
    UI::Text m_welcome;
    UI::Text m_highscoreTitle;
    std::array<UI::Text, 4> m_highscores;

    std::string m_nickname = "";

    //  0  ,  1  ,  2  ,   3   ,  4  ,     5
    // Play, Exit, Easy, Medium, Hard, Impossible
    std::array<UI::Button, 6> m_buttons;

    Enums::Difficulty m_difficulty = Consts::STARTING_DIFFICULTY;
    Enums::HomeButton m_currentClickedButton = Enums::HomeButton::None;
    
    HomeScenePlayer m_player;
    bool m_isLoading = false;

    void resetButtonsColor();
    void resetDifficultyButtonsColor();
    void checkDifficultyButton(); 
    virtual raylib::Color checkButton(GameManager& gameManager, const raylib::Color &hoverColor, 
        const raylib::Color& clickedColor, int buttonId) override;

public:
    HomeScene();

    ~HomeScene() = default;

    virtual void initUI(const GameManager &gameManager) override;
    virtual void update(GameManager& gameManager) override;
    virtual void render() override;
    virtual void renderUI(const raylib::Camera2D& camera) override;
    
    Enums::Difficulty getDifficulty() const;
};