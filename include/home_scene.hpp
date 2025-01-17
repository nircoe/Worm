#pragma once

#include "scene.hpp"
#include "raylib-cpp.hpp"
#include "home_scene_player.hpp"
#include "auxiliary/consts.hpp"
#include "auxiliary/utils.hpp"
#include "auxiliary/enums.hpp"
#include <string>

namespace raylib { class Color; class Vector2; class Rectangle; }

class HomeScene : public Scene
{
    const std::string m_titleText = "Worm";

    //  0  ,  1  ,  2  ,   3   ,  4  ,     5
    // Play, Exit, Easy, Medium, Hard, Impossible
    const std::size_t m_arraysSize = 6;
    std::array<raylib::Color, 6> m_buttonsColors;
    std::array<raylib::Vector2, 6> m_buttonsTextPosition;

    raylib::Vector2 m_titlePosition;

    Enums::Difficulty m_difficulty = Consts::STARTING_DIFFICULTY;
    Enums::HomeButton m_currentClickedButton = Enums::HomeButton::None;
    
    HomeScenePlayer m_player;

    void resetButtonsColor();
    void resetDifficultyButtonsColor();
    void checkDifficultyButton();
    raylib::Color checkButton(SceneManager& sceneManager, const raylib::Color &hoverColor, 
        const raylib::Color& clickedColor, Enums::HomeButton button);
    void checkButtons(SceneManager& sceneManager, const raylib::Vector2& mousePosition);
    const bool checkButtonHover(const raylib::Vector2& mousePosition, const raylib::Rectangle& rect);
    

public:
    HomeScene();

    ~HomeScene() = default;

    void update(SceneManager& sceneManager) override;
    void render() override;
    void renderUI(const raylib::Font& font) override;

    Enums::Difficulty getDifficulty() const;

    void calculateTextsPositions(const raylib::Font& font) override;
};