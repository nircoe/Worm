#pragma once

#include "scene.hpp"
#include "raylib-cpp.hpp"
#include "home_scene_player.hpp"
#include "auxiliary/consts.hpp"
#include "auxiliary/utils.hpp"
#include "auxiliary/enums.hpp"
#include "ui/button.hpp"
#include "ui/textbox.hpp"
#include "ui/text.hpp"
#include <string>

namespace raylib { class Color; class Vector2; class Rectangle; }

class NewGameScene : public Scene
{
    UI::Text m_title;
    UI::Text m_subtitle;
    const std::string m_titleText = "Welcome!";
    const std::string m_subtitleText = "Please choose a nickname or continue as guest";

    //        0        ,        1
    // Play as nickname, Play as guest
    std::array<UI::Button, 2> m_buttons;

    raylib::Vector2 m_titlePosition;
    raylib::Vector2 m_subtitlePosition;

    Enums::NewGameButton m_currentClickedButton = Enums::NewGameButton::None;

    UI::TextBox m_textBox;

    void resetButtonsColor();

    virtual raylib::Color checkButton(GameManager& gameManager, const raylib::Color &hoverColor, 
        const raylib::Color& clickedColor, int buttonId) override;

public:
    NewGameScene();

    ~NewGameScene() = default;

    virtual void update(GameManager& gameManager) override;
    virtual void render() override;
    virtual void renderUI(const raylib::Font& font, const raylib::Camera2D& camera) override;

    virtual void initUI(const GameManager &gameManager) override;
};