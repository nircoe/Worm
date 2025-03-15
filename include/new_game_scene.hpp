#pragma once

#include "scene.hpp"
#include "raylib-cpp.hpp"
#include "home_scene_player.hpp"
#include "auxiliary/consts.hpp"
#include "auxiliary/utils.hpp"
#include "auxiliary/enums.hpp"
#include "ui/button.hpp"
#include <string>

namespace raylib { class Color; class Vector2; class Rectangle; }

class NewGameScene : public Scene
{
    const std::string m_titleText = "Welcome!";
    const std::string m_subTitleText = "Please choose a nickname or continue as guest";

    //        0        ,        1
    // Play as nickname, Play as guest
    std::array<UI::Button, 2> m_buttons;

    raylib::Rectangle m_background;
    raylib::Vector2 m_titlePosition;
    raylib::Vector2 m_subTitlePosition;

    Enums::HomeButton m_currentClickedButton = Enums::HomeButton::None;

    void resetButtonsColor();

    virtual raylib::Color checkButton(GameManager& gameManager, const raylib::Color &hoverColor, 
        const raylib::Color& clickedColor, int buttonId) override;

public:
    NewGameScene();

    ~NewGameScene() = default;

    virtual void update(GameManager& gameManager) override;
    virtual void render() override;
    virtual void renderUI(const raylib::Font& font, const raylib::Camera2D& camera) override;

    virtual void initUI(const raylib::Font& font) override;
};